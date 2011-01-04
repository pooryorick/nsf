# 
# C-Code generator to generate stubs to handle all objv-parsing from
# an simple interface definition language. This guarantees consistent
# handling of input argument types, consistent error messages in case
# of failures and eases documentation.
#
# Gustaf Neumann,                                fecit in June 2009
#

set ::converter ""
set ::objCmdProc "(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv \[\]);"

proc convertername {type argname} {
  return [string totitle [string trimleft $argname -]]
}

proc createconverter {type argname} {
  set name [convertername $type $argname]
  if {[info exists ::createdConverter($name)]} {
    return ""
  }
  set domain [split $type |]
  set opts "static CONST char *opts\[\] = {\"[join $domain {", "}]\", NULL};"
  set ::createdConverter($name) "ConvertTo${name}, \"$type\""
  set enums [list ${name}NULL]
  foreach d $domain {lappend enums $name[string totitle [string map [list - _] $d]]Idx}
  subst {
enum ${name}Idx {[join $enums {, }]};

static int ConvertTo${name}(Tcl_Interp *interp, Tcl_Obj *objPtr, NsfParam CONST *pPtr, 
			    ClientData *clientData, Tcl_Obj **outObjPtr) {
  int index, result;
  $opts
  (void)pPtr;
  result = Tcl_GetIndexFromObj(interp, objPtr, opts, "$argname", 0, &index);
  *clientData = (ClientData) INT2PTR(index + 1);
  *outObjPtr = objPtr;
  return result;
}
  }
}

proc genifd {parameterDefinitions} {
  set l [list]
  foreach parameterDefinition $parameterDefinitions {
    array set "" $parameterDefinition
    switch $(-type) {
      "" {set type NULL}
      default {set type $(-type)}
    }
    set flags [expr {$(-required) ? "NSF_ARG_REQUIRED" : "0"}]
    set argName $(-argName)
    switch -glob $type {
      "NULL"       {set converter String}
      "boolean"    {set converter Boolean}
      "switch"     {set converter Boolean}
      "class"      {set converter Class}
      "object"     {set converter Object}
      "tclobj"     {set converter Tclobj}
      "args"       {set converter Nothing}
      "allargs"    {set converter Nothing}
      "objpattern" {set converter Objpattern}
      *|* {  
        set converter [convertername $type $(-argName)]
        append ::converter [createconverter $type $(-argName)]
        set (-argName) $type
	append flags |NSF_ARG_IS_ENUMERATION
      }
    }
    # this does not work, since initializer element is not constant.
#     if {[info exists (-default)]} {
#       puts stderr "default of $argName = '$(-default)'"
#       set default ", Tcl_NewStringObj(\"$(-default)\",-1)"
#     } else {
#       set default ""
#     }
    lappend l "{\"$argName\", $flags, $(-nrargs), ConvertTo$converter}"
  }
  if {[llength $l] == 0} {
    return "{NULL, 0, 0, NULL}"
  } else {
    return [join $l ",\n  "]
  }
}

proc gencall {fn parameterDefinitions clientData cDefsVar ifDefVar arglistVar preVar postVar introVar} {
  upvar $cDefsVar cDefs $ifDefVar ifDef $arglistVar arglist $preVar pre $postVar post \
      $introVar intro 
  set c [list]
  set i 0
  set pre ""; set post ""
  set intro ""

  switch $clientData {
    class {
      set a  [list cl]
      set if [list "NsfClass *cl"]
      append intro \
          "  NsfClass *cl =  NsfObjectToClass(clientData);" \n \
          {  if (!cl) return NsfObjErrType(interp, NULL, objv[0], "Class", NULL);}
    }
    object {
      set a  [list obj]
      set if [list "NsfObject *obj"]
      append intro \
          "  NsfObject *obj =  (NsfObject *)clientData;" \n \
          {  if (!obj) return NsfObjErrType(interp, NULL, objv[0], "Object", NULL);}
    }
    ""    {
      append intro "  (void)clientData;\n"
      set a [list]
      set if [list]
      array set cd {arglist "" ifDefs ""}
    }
  }
  foreach parameterDefinition $parameterDefinitions {
    array set "" $parameterDefinition
    set ifSet 0
    set cVar 1
    set (-argName) [string map [list - _] $(-argName)]
    if {[regexp {^_(.*)$} $(-argName) _ switchName]} {
      set varName with[string totitle $switchName]
      set calledArg $varName
      set type "int "
      if {$(-nrargs) == 1} {
        switch -glob $(-type) {
          ""           {set type "CONST char *"}
          "class"      {set type "NsfClass *"}
          "object"     {set type "NsfObject *"}
          "tclobj"     {set type "Tcl_Obj *"}
          "*|*"        {set type "int "}
          default      {error "type '$(-type)' not allowed for parameter"}
        }
      }
    } else {
      set varName $(-argName)
      set calledArg $varName
      switch -glob $(-type) {
        ""           {set type "CONST char *"}
        "boolean"    {set type "int "}
        "class"      {set type "NsfClass *"}
        "object"     {set type "NsfObject *"}
        "tclobj"     {set type "Tcl_Obj *"}
        "args"       {
          set type "int "
          set calledArg "objc-pc.lastobjc, objv+pc.lastobjc"
          lappend if "int nobjc" "Tcl_Obj *CONST nobjv\[\]"
          set ifSet 1
          set cVar 0
        }
        "allargs"       {
          set type "int "
          set calledArg "objc, objv"
          lappend if "int objc" "Tcl_Obj *CONST objv\[\]"
          set ifSet 1
          set cVar 0
        }
        "objpattern" {
          set type "Tcl_Obj *"
          lappend c "CONST char *${varName}String = NULL;" "NsfObject *${varName}Obj = NULL;"
          set calledArg "${varName}String, ${varName}Obj"
          lappend if "CONST char *${varName}String" "NsfObject *${varName}Obj"
          set ifSet 1
          append pre [subst -nocommands {
    if (GetMatchObject(interp, ${varName}, objc>$i ? objv[$i] : NULL, &${varName}Obj, &${varName}String) == -1) {
      if (${varName}) {
        DECR_REF_COUNT(${varName});
      }
      return TCL_OK;
    }
          }]
	  append post [subst -nocommands {
    if (${varName}) {
      DECR_REF_COUNT(${varName});
    }
         }]
	  # end of obj pattern
        }
        *|* {set type "int "}
        default  {
          error "type '$(-type)' not allowed for argument"
        }
      }
    }
    if {!$ifSet} {lappend if "$type$varName"}
    if {$cVar} {
      if {$type eq "int "} {
        lappend c [subst -nocommands {$type$varName = ($type)PTR2INT(pc.clientData[$i]);}]
      } else {
        lappend c [subst -nocommands {$type$varName = ($type)pc.clientData[$i];}]
      }
    }
    lappend a $calledArg
    incr i
  }
  set ifDef   [join $if ", "]
  set cDefs   [join $c "\n    "]
  set arglist [join $a ", "]
}

proc genStub {stub intro obj idx cDefs pre call post} {
  # Tiny optimization for calls without parameters;
  # ParseContextExtendObjv() is just called for procs, so no need to
  # free non-static objvs. Actually, the api for c-methods does
  # not allow to generate structures which have to be freed.
  # we assert this in the code.
  if {$cDefs ne ""} {
    set releasePC "ParseContextRelease(&pc);"
    set releasePC "assert(pc.status == 0);"
  } else {
    set releasePC ""
  }
  return [subst -nocommands {
static int
${stub}(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  ParseContext pc;
$intro
  if (ArgumentParse(interp, objc, objv, $obj, objv[0], 
                     method_definitions[$idx].paramDefs, 
                     method_definitions[$idx].nrParameters, 1,
                     &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    $cDefs
$pre
    $releasePC
    $call
$post
  }
}
}]}

proc genSimpleStub {stub intro idx cDefs pre call post} {
  return [subst -nocommands {
static int
${stub}(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
$intro
    $cDefs
$pre
    $call
$post
}
}]}

proc implArgList {implementation prefix arglist} {
  if {$arglist ne ""} {
    return "${implementation}(${prefix}interp, $arglist)"
  }
  return "${implementation}(${prefix}interp)"
}

proc genstubs {} {
  set stubDecls ""
  set decls ""
  set enums [list]
  set ifds [list]
  foreach key [lsort [array names ::definitions]] {
    array set d $::definitions($key)
    lappend enums $d(idx)
    set nrArgs [llength $d(parameterDefinitions)]
    set stubDecl "static int $d(stub)$::objCmdProc\n"
    set ifd "{\"$d(ns)::$d(methodName)\", $d(stub), $nrArgs, {\n  [genifd $d(parameterDefinitions)]}\n}"
    
    gencall $d(stub) $d(parameterDefinitions) $d(clientData) cDefs ifDef arglist pre post intro 
    append decls "static int [implArgList $d(implementation) {Tcl_Interp *} $ifDef];\n"
    if {$post ne ""} {
      append cDefs "\n    int returnCode;"
      set call "returnCode = [implArgList $d(implementation) {} $arglist];"
      set post [string trimright $post]
      append post "\n    return returnCode;"
    } else {
      set call "return [implArgList $d(implementation) {} $arglist];"
    }
    
    #if {$nrArgs == 1} { puts stderr "$d(stub) => '$arglist' cDefs=$cDefs ifd=$ifDef" }
    if {$nrArgs == 1 && $arglist eq "objc, objv"} {
      # TODO we would not need to generate a stub at all.... 
      #set ifd "{\"$d(ns)::$d(methodName)\", $d(implementation), $nrArgs, {\n  [genifd $d(parameterDefinitions)]}\n}"
      #set stubDecl "static int $d(implementation)$::objCmdProc\n"
      append fns [genSimpleStub $d(stub) $intro $d(idx) $cDefs $pre $call $post]
    } elseif {$nrArgs == 1 && $arglist eq "obj, objc, objv"} {
      # no need to call objv parser
      #puts stderr "$d(stub) => '$arglist'"
      append fns [genSimpleStub $d(stub) $intro $d(idx) $cDefs $pre $call $post]
  } elseif {$nrArgs == 0} {
    append pre [subst -nocommands {
      if (objc != 1) {
	return ArgumentError(interp, "too many arguments:", 
			     method_definitions[$d(idx)].paramDefs,
			     NULL, objv[0]); 
      } 
    }]
    append fns [genSimpleStub $d(stub) $intro $d(idx) $cDefs $pre $call $post]
  } elseif {$nrArgs == 1 && [string match "Tcl_Obj *" $cDefs]} {

    array set defs [list -required 0]
    array set defs [lindex $d(parameterDefinitions) 0]
    
    if {$defs(-required)} {
      set op "objc != 2"
    } else {
      set op "objc < 1 || objc > 2"
    }
    append pre [subst -nocommands {
      if ($op) {
	return ArgumentError(interp, "wrong # of arguments:", 
			     method_definitions[$d(idx)].paramDefs,
			     NULL, objv[0]); 
      }
    }]

    set newArg {objc == 2 ? objv[1] : NULL}
    if {[regexp {^(.*),(.*)$} $arglist _ arg1]} {
      set newArglist "$arg1, $newArg"
    } else {
      set newArglist $newArg
    }
    regsub ", $arglist\\)" $call ", $newArglist\)" call
    
    append fns [genSimpleStub $d(stub) $intro $d(idx) "" $pre $call $post]
  } else {
      switch $d(methodType) {
        objectMethod {set obj "obj"}
        classMethod {set obj "(NsfObject *) cl"}
        default {set obj "NULL"}
      }
      append fns [genStub $d(stub) $intro $obj $d(idx) $cDefs $pre $call $post]
    }
    lappend ifds $ifd
    append stubDecls $stubDecl
  }
  
  puts {
typedef struct {
  CONST char *methodName;
  Tcl_ObjCmdProc *proc;
  int nrParameters;
  NsfParam paramDefs[12];
} methodDefinition;
   }
   puts $::converter

   set entries [list]
   foreach c [array names ::createdConverter] {lappend entries "\{$::createdConverter($c)\}"}
   puts [subst {
static enumeratorConverterEntry enumeratorConverterEntries\[\] = {
  [join $entries ",\n  "],
  {NULL, NULL}
};
   }]

   puts {
static int ArgumentParse(Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[], 
                         NsfObject *obj, Tcl_Obj *procName,
                         NsfParam CONST *paramPtr, int nrParameters, int doCheck,
			 ParseContext *pc);

static int GetMatchObject(Tcl_Interp *interp, Tcl_Obj *patternObj, Tcl_Obj *origObj,
			  NsfObject **matchObject, CONST char **pattern);

/* just to define the symbol */
static methodDefinition method_definitions[];
  }

  set namespaces [list]
  foreach {key value} [array get ::ns] {
     # no need to create the ::nsf namespace
     if {$value eq "::nsf"} continue
     lappend namespaces "\"$value\"" 
  }
  set namespaceString [join $namespaces ",\n  "]
  puts "static CONST char *method_command_namespace_names\[\] = {\n  $namespaceString\n};"
  puts $stubDecls
  puts $decls
  set enumString [join $enums ",\n "]
  puts "enum {\n $enumString\n} NsfMethods;\n"
  puts $fns
  set definitionString [join $ifds ",\n"]
  puts "static methodDefinition method_definitions\[\] = \{\n$definitionString,\{NULL\}\n\};\n"
}

proc methodDefinition {methodName methodType implementation parameterDefinitions {ns ""}} {
  set d(methodName) $methodName
  set d(implementation) $implementation
  set d(stub) ${implementation}Stub
  set d(idx) ${implementation}Idx
  set d(methodType) $methodType
  if {$ns eq ""} {set ns $::ns($methodType)}
  set d(ns) $ns
  switch $methodType {
    classMethod  {set d(clientData) class}
    objectMethod {set d(clientData) object}
    default      {set d(clientData) ""}
  }
  set completed [list]
  foreach parameterDefinition $parameterDefinitions {
    array set "" {-required 0 -nrargs 0 -type ""}
    array set "" $parameterDefinition
    lappend completed [array get ""]
  }
  set d(parameterDefinitions) $completed
  set ::definitions($d(methodType)-$d(implementation)-$d(methodName)) [array get d]
}

proc checkMethod {methodName implementation parameterDefinitions} {
  methodDefinition type=$methodName checkMethod $implementation $parameterDefinitions
}
proc classMethod {methodName implementation parameterDefinitions} {
  methodDefinition $methodName classMethod $implementation $parameterDefinitions
}
proc objectMethod {methodName implementation parameterDefinitions} {
  methodDefinition $methodName objectMethod $implementation $parameterDefinitions
}
proc objectInfoMethod {methodName implementation parameterDefinitions} {
  methodDefinition $methodName objectMethod $implementation $parameterDefinitions $::ns(objectInfoMethod)
}
proc classInfoMethod {methodName implementation parameterDefinitions} {
  methodDefinition $methodName classMethod $implementation $parameterDefinitions $::ns(classInfoMethod)
}
proc nsfCmd {methodName implementation parameterDefinitions} {
  methodDefinition $methodName nsfCmd $implementation $parameterDefinitions
}

source [file dirname [info script]]/gentclAPI.decls

genstubs
puts stderr "[array size ::definitions] parsing stubs generated"
