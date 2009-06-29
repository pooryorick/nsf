
# objectMethod
# classMethod
# infoObjectMethod
# infoClassMethod
# checkMethod

set objCmdProc "(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv \[\]);"
proc genifd {argDefinitions} {
  set l [list]
  foreach argDefinition $argDefinitions {
    array set "" $argDefinition
    switch $(-type) {
      "" {set type NULL}
      default {set type "\"$(-type)\""}
    }
    lappend l "{\"$(-argName)\", $(-required), $(-nrargs), $type}"
  }
  join $l ",\n  "
}

proc gencall {argDefinitions clientData cDefsVar ifDefVar arglistVar preVar postVar introVar} {
  upvar $cDefsVar cDefs $ifDefVar ifDef $arglistVar arglist $preVar pre $postVar post \
      $introVar intro 
  set c [list]
  set a [list]
  set i 0
  set pre ""; set post ""
  foreach argDefinition $argDefinitions {
    array set "" $argDefinition
    set ifSet 0
    set cVar 1
    if {[regexp {^-(.*)$} $(-argName) _ switchName]} {
      set varName with[string totitle $switchName]
      set calledArg $varName
      set type "int "
      if {$(-nrargs) == 1} {
        switch $(-type) {
          ""           {set type "char *"}
          "class"      {set type "XOTclClass *"}
          "object"     {set type "XOTclObject *"}
          "tclobj"     {set type "Tcl_Obj *"}
          default      {error "type '$(-type)' not allowed for parameter"}
        }
      }
    } else {
      set varName $(-argName)
      set calledArg $varName
      switch $(-type) {
        ""           {set type "char *"}
        "class"      {set type "XOTclClass *"}
        "object"     {set type "XOTclObject *"}
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
          lappend c "char *${varName}String = NULL;" "XOTclObject *${varName}Obj = NULL;"
          set calledArg "${varName}String, ${varName}Obj"
          lappend if "char *${varName}String" "XOTclObject *${varName}Obj"
          set ifSet 1
          append pre [subst -nocommands {
    if (getMatchObject3(interp, ${varName},  &pc, &${varName}Obj, &${varName}String) == -1) {
      return TCL_OK;
    }
          }]
#          append post [subst -nocommands {
#    if (${varName}Obj) {
#      Tcl_SetObjResult(interp, returnCode ? ${varName}Obj->cmdName : XOTclGlobalObjects[XOTE_EMPTY]);
#    }
#          }]
        }
        default  {error "type '$(-type)' not allowed for argument"}
      }
    }
    if {!$ifSet} {lappend if "$type$varName"}
    if {$cVar} {lappend c [subst -nocommands {$type $varName = ($type)pc.clientData[$i];}]}
    lappend a $calledArg
    incr i
  }
  set intro "  parseContext pc;\n"
  switch $clientData {
    class {
      array set cd {arglist "cl, " ifDefs "XOTclClass *cl, "}
      append intro \
          "  XOTclClass *cl =  XOTclObjectToClass(clientData);" \n \
          {  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");}
    }
    ""    {
      array set cd {arglist "" ifDefs ""}
    }
  }
  set ifDef $cd(ifDefs)[join $if ", "]
  set cDefs [join $c "\n    "]
  set arglist $cd(arglist)[join $a ", "]
}


proc genifds {} {
  set stubDecls ""
  set decls ""
  set enums [list]
  set ifds [list]
  foreach key [lsort [array names ::definitions]] {
    array set d $::definitions($key)
    append stubDecls "static int $d(stub)$::objCmdProc\n"
    lappend enums $d(idx)
    lappend ifds "{\"$d(methodName)\", $d(stub), {\n  [genifd $d(argDefinitions)]}\n}"

    gencall $d(argDefinitions) $d(clientData) cDefs ifDef arglist pre post intro 
    append decls "static int $d(implementation)(Tcl_Interp *interp, $ifDef);\n"
    if {$post ne ""} {
      append cDefs "\n    int returnCode;"
      set call "returnCode = $d(implementation)(interp, $arglist);"
      set post [string trimright $post]
      append post "\n    return TCL_OK;"
    } else {
      set call "return $d(implementation)(interp, $arglist);"
    }
    append fns [subst -nocommands {
static int
$d(stub)(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
$intro
  if (parse2(interp, objc, objv, $d(idx), &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    $cDefs
$pre
    $call
$post
  }
}
  }]
  }

  puts {
typedef struct {
  char *methodName;
  Tcl_ObjCmdProc *proc;
  CONST interfaceDefinition ifd;
} methodDefinition2;

static int parse2(Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[],
                  int idx, parseContext *pc);

static int getMatchObject3(Tcl_Interp *interp, Tcl_Obj *patternObj,  parseContext *pc,
                           XOTclObject **matchObject, char **pattern);
  }
  puts $stubDecls
  puts $decls
  set enumString [join $enums ",\n "]
  puts "enum {\n $enumString\n} XOTclMethods;\n"
  puts $fns
  set definitionString [join $ifds ",\n"]
  puts "static methodDefinition2 methodDefinitons\[\] = \{\n$definitionString\n\};\n"
}

proc methodDefinition {methodName methodType implementation argDefinitions} {
  set d(methodName) $methodName
  set d(implementation) $implementation
  set d(stub) ${implementation}Stub
  set d(idx) ${implementation}Idx
  set d(methodType) $methodType
  switch $methodType {
    classMethod  {set d(clientData) class}
    objectMethod {set d(clientData) object}
    default      {set d(clientData) ""}
  }
  set completed [list]
  foreach argDefinition $argDefinitions {
    array set "" {-required 0 -nrargs 0 -type ""}
    array set "" $argDefinition
    lappend completed [array get ""]
  }
  set d(argDefinitions) $completed
  set ::definitions($d(methodType)-$d(implementation)-$d(methodName)) [array get d]
}

proc infoClassMethod {methodName implementation argDefinitions} {
  methodDefinition $methodName infoClassMethod $implementation $argDefinitions
}

proc infoObjectMethod {methodName implementation argDefinitions} {
  methodDefinition $methodName infoObjectMethod $implementation $argDefinitions
}

proc checkMethod {methodName implementation argDefinitions} {
  methodDefinition type=$methodName checkMethod $implementation $argDefinitions
}
proc classMethod {methodName implementation argDefinitions} {
  methodDefinition $methodName classMethod $implementation $argDefinitions
}


#
# class methods
#
classMethod alloc XOTclCAllocMethod {
  {-argName "name" -required 1}
}
classMethod create XOTclCCreateMethod {
  {-argName "name" -required 1}
  {-argName "args" -required 1 -type allargs}
}
classMethod dealloc XOTclCDeallocMethod {
  {-argName "object" -required 1 -type tclobj}
}
classMethod new XOTclCNewMethod {
  {-argName "-childof" -type object -nrargs 1}
  {-argName "args" -required 0 -type args}
}
classMethod instfilterguard XOTclCInstFilterGuardMethod {
  {-argName "filter" -required 1}
  {-argName "guard" -required 1 -type tclobj}
}
classMethod instinvar XOTclCInvariantsMethod {
  {-argName "invariantlist" -required 1 -type tclobj}
}
classMethod instmixinguard XOTclCInstMixinGuardMethod {
  {-argName "mixin" -required 1}
  {-argName "guard" -required 1 -type tclobj}
}
classMethod instparametercmd XOTclCInstParameterCmdMethod {
  {-argName "name" -required 1}
}
classMethod instproc XOTclCInstProcMethod {
  {-argName "name" -required 1 -type tclobj}
  {-argName "args" -required 1 -type tclobj}
  {-argName "body" -required 1 -type tclobj}
  {-argName "precondition"  -type tclobj}
  {-argName "postcondition" -type tclobj}
}
classMethod classscopedinstproc XOTclCInstProcMethodC {
  {-argName "name" -required 1 -type tclobj}
  {-argName "args" -required 1 -type tclobj}
  {-argName "body" -required 1 -type tclobj}
  {-argName "precondition"  -type tclobj}
  {-argName "postcondition" -type tclobj}
}
classMethod instforward XOTclCInstForwardMethod {
  {-argName "method" -required 1 -type tclobj}
  {-argName "-default" -nrargs 1 -type tclobj}
  {-argName "-earlybinding"}
  {-argName "-methodprefix" -nrargs 1 -type tclobj}
  {-argName "-objscope"}
  {-argName "-onerror" -nrargs 1 -type tclobj}
  {-argName "-verbose"}
  {-argName "target" -type tclobj}
  {-argName "args" -type args}
}
# todo -protected for XOTclCInstForwardMethod
classMethod recreate XOTclCRecreateMethod {
  {-argName "name" -required 1 -type tclobj}
  {-argName "args" -required 1 -type allargs}
}
classMethod unknown XOTclCUnknownMethod {
  {-argName "name" -required 1}
  {-argName "args" -required 1 -type allargs}
}

#
# check methods
#
checkMethod required XOTclCheckRequiredArgs {
  {-argName "name" -required 1}
  {-argName "value" -required 0 -type tclobj}
}
checkMethod boolean XOTclCheckBooleanArgs {
  {-argName "name" -required 1}
  {-argName "value" -required 0 -type tclobj}
}

#
# info object methods
#
infoObjectMethod args XOTclObjInfoArgsMethod {
  {-argName "object" -required 1 -type object}
  {-argName "methodName" -required 1}
}
infoObjectMethod body XOTclObjInfoBodyMethod {
  {-argName "object" -required 1 -type object}
  {-argName "methodName" -required 1}
}
infoObjectMethod check XOTclObjInfoCheckMethod {
  {-argName "object" -required 1 -type object}
}
infoObjectMethod children XOTclObjInfoChildrenMethod {
  {-argName "object" -required 1 -type object}
  {-argName "pattern" -required 0}
}
infoObjectMethod class XOTclObjInfoClassMethod {
  {-argName "object" -required 1 -type object}
}
infoObjectMethod commands XOTclObjInfoCommandsMethod {
  {-argName "object" -required 1 -type object}
  {-argName "pattern" -required 0}
}
infoObjectMethod default XOTclObjInfoDefaultMethod {
  {-argName "object" -required 1 -type object}
  {-argName "methodName" -required 1}
  {-argName "arg" -required 1}
  {-argName "var" -required 1 -type tclobj}
}
infoObjectMethod filter XOTclObjInfoFilterMethod {
  {-argName "object" -required 1 -type object}
  {-argName "-order"}
  {-argName "-guards"}
  {-argName "pattern"}
}
infoObjectMethod filterguard XOTclObjInfoFilterguardMethod {
  {-argName "object" -required 1 -type object}
  {-argName "filter" -required 1}
}
infoObjectMethod forward XOTclObjInfoForwardMethod {
  {-argName "object" -required 1 -type object}
  {-argName "-definition"}
  {-argName "methodName" -required 1}
}
infoObjectMethod hasnamespace XOTclObjInfoHasnamespaceMethod {
  {-argName "object" -required 1 -type object}
}
infoObjectMethod invar XOTclObjInfoInvarMethod {
  {-argName "object" -required 1 -type object}
}
infoObjectMethod methods XOTclObjInfoMethodsMethod {
  {-argName "object" -required 1 -type object}
  {-argName "-noprocs"}
  {-argName "-nocmds"}
  {-argName "-nomixins"}
  {-argName "-incontext"}
  {-argName "pattern"}
}
infoObjectMethod mixin XOTclObjInfoMixinMethod {
  {-argName "object" -required 1 -type object}
  {-argName "-guards"}
  {-argName "-order"}
  {-argName "pattern" -type objpattern}
}
infoObjectMethod mixinguard XOTclObjInfoMixinguardMethod {
  {-argName "object" -required 1 -type object}
  {-argName "mixin"  -required 1}
}
infoObjectMethod nonposargs XOTclObjInfoNonposargsMethod {
  {-argName "object" -required 1 -type object}
  {-argName "methodName" -required 1}
}
infoObjectMethod parent XOTclObjInfoParentMethod {
  {-argName "object" -required 1 -type object}
}
infoObjectMethod parametercmd XOTclObjInfoParametercmdMethod {
  {-argName "object" -required 1 -type object}
  {-argName "pattern"}
}
infoObjectMethod post XOTclObjInfoPostMethod {
  {-argName "object" -required 1 -type object}
  {-argName "methodName" -required 1}
}
infoObjectMethod pre XOTclObjInfoPreMethod {
  {-argName "object" -required 1 -type object}
  {-argName "methodName" -required 1}
}
infoObjectMethod precedence XOTclObjInfoPrecedenceMethod {
  {-argName "object" -required 1 -type object}
  {-argName "-intrinsic"}
  {-argName "pattern" -required 0}
}
infoObjectMethod procs XOTclObjInfoProcsMethod {
  {-argName "object" -required 1 -type object}
  {-argName "pattern" -required 0}
}
infoObjectMethod slotobjects XOTclObjInfoSlotObjectsMethod {
  {-argName "object" -required 1 -type object}
  {-argName "pattern" -required 0}
}
infoObjectMethod vars XOTclObjInfoVarsMethod {
  {-argName "object" -required 1 -type object}
  {-argName "pattern" -required 0}
}


#
# info class methods
#
infoClassMethod instances XOTclClassInfoHeritageMethod {
  {-argName "class"   -required 1 -type class}
  {-argName "pattern"}
}

infoClassMethod instances XOTclClassInfoInstancesMethod {
  {-argName "class"   -required 1 -type class}
  {-argName "-closure"}
  {-argName "pattern" -type objpattern}
}

infoClassMethod instargs XOTclClassInfoInstargsMethod {
  {-argName "class" -required 1 -type class}
  {-argName "methodName" -required 1}
}

infoClassMethod instbody XOTclClassInfoInstbodyMethod {
  {-argName "class" -required 1 -type class}
  {-argName "methodName" -required 1}
}

infoClassMethod instances XOTclClassInfoInstcommandsMethod {
  {-argName "class"   -required 1 -type class}
  {-argName "pattern"}
}

infoClassMethod instdefault XOTclClassInfoInstdefaultMethod {
  {-argName "class"   -required 1 -type class}
  {-argName "methodName" -required 1}
  {-argName "arg" -required 1}
  {-argName "var" -required 1 -type tclobj}
}

infoClassMethod instfilter XOTclClassInfoInstfilterMethod {
  {-argName "class"   -required 1 -type class}
  {-argName "-guards"}
  {-argName "pattern"}
}

infoClassMethod instfilterguard XOTclClassInfoInstfilterguardMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "filter" -required 1}
}

infoClassMethod instforward XOTclClassInfoInstforwardMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "-definition"}
  {-argName "methodName" -required 1}
}

infoClassMethod instinvar XOTclClassInfoInstinvarMethod {
  {-argName "class"  -required 1 -type class}
}

infoClassMethod instmixin XOTclClassInfoInstmixinMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "-closure"}
  {-argName "-guards"}
  {-argName "pattern" -type objpattern}
}

infoClassMethod instmixinguard XOTclClassInfoInstmixinguardMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "mixin" -required 1}
}

infoClassMethod instmixinof XOTclClassInfoInstmixinofMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "-closure"}
  {-argName "pattern" -type objpattern}
}

infoClassMethod instnonposargs XOTclClassInfoInstnonposargsMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "methodName" -required 1}
}

infoClassMethod instparametercmd XOTclClassInfoInstparametercmdMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "pattern"}
}

infoClassMethod instpost XOTclClassInfoInstpostMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "methodName" -required 1}
}

infoClassMethod instpre XOTclClassInfoInstpreMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "methodName" -required 1}
}

infoClassMethod instprocs XOTclClassInfoInstprocsMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "pattern"}
}

infoClassMethod mixinof XOTclClassInfoMixinofMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "-closure"}
  {-argName "pattern" -type objpattern}
}

infoClassMethod parameter XOTclClassInfoParameterMethod {
  {-argName "class"  -required 1 -type class}
}

infoClassMethod slots XOTclClassInfoSlotsMethod {
  {-argName "class"  -required 1 -type class}
}

infoClassMethod subclass XOTclClassInfoSubclassMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "-closure"}
  {-argName "pattern" -type objpattern}
}

infoClassMethod superclass XOTclClassInfoSuperclassMethod {
  {-argName "class"  -required 1 -type class}
  {-argName "-closure"}
  {-argName "pattern"}
}


genifds