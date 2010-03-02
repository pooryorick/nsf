static char cmd[] = 
"namespace eval ::xotcl {\n"
"set bootstrap 1}\n"
"namespace eval xotcl2 {\n"
"namespace path ::xotcl\n"
"::xotcl::createobjectsystem ::xotcl2::Object ::xotcl2::Class\n"
"foreach cmd [info command ::xotcl::cmd::Object::*] {\n"
"set cmdName [namespace tail $cmd]\n"
"if {$cmdName in [list \"instvar\"]} continue\n"
"::xotcl::alias Object $cmdName $cmd}\n"
"::xotcl::alias Object eval -nonleaf ::eval\n"
"foreach cmd [info command ::xotcl::cmd::Class::*] {\n"
"set cmdName [namespace tail $cmd]\n"
"::xotcl::alias Class $cmdName $cmd}\n"
"foreach cmd [list __next cleanup  noinit residualargs uplevel upvar] {\n"
"::xotcl::methodproperty Object $cmd protected 1}\n"
"foreach cmd [list recreate] {\n"
"::xotcl::methodproperty Class $cmd protected 1}\n"
"::xotcl::methodproperty Object destroy redefine-protected true\n"
"::xotcl::methodproperty Class  alloc   redefine-protected true\n"
"::xotcl::methodproperty Class  dealloc redefine-protected true\n"
"::xotcl::methodproperty Class  create  redefine-protected true\n"
"::xotcl::method Class method {\n"
"name arguments body -precondition -postcondition} {\n"
"set conditions [list]\n"
"if {[info exists precondition]}  {lappend conditions -precondition  $precondition}\n"
"if {[info exists postcondition]} {lappend conditions -postcondition $postcondition}\n"
"::xotcl::method [::xotcl::current object] $name $arguments $body {*}$conditions}\n"
"::xotcl::method Object method {\n"
"name arguments body -precondition -postcondition} {\n"
"set conditions [list]\n"
"if {[info exists precondition]}  {lappend conditions -precondition  $precondition}\n"
"if {[info exists postcondition]} {lappend conditions -postcondition $postcondition}\n"
"::xotcl::method [::xotcl::current object] -per-object $name $arguments $body {*}$conditions}\n"
"Class eval {\n"
":method object {what args} {\n"
"if {$what in [list \"alias\" \"attribute\" \"forward\" \"method\" \"setter\"]} {\n"
"return [::xotcl::dispatch [::xotcl::current object] ::xotcl::classes::xotcl2::Object::$what {*}$args]}\n"
"if {$what in [list \"info\"]} {\n"
"return [::xotcl2::objectInfo [lindex $args 0] [::xotcl::current object] {*}[lrange $args 1 end]]}\n"
"if {$what in [list \"filter\" \"mixin\"]} {\n"
"return [:object-$what {*}$args]}\n"
"if {$what in [list \"filterguard\" \"mixinguard\"]} {\n"
"return [::xotcl::dispatch [::xotcl::current object] ::xotcl::cmd::Object::$what {*}$args]}}\n"
":method unknown {m args} {\n"
"error \"Method '$m' unknown for [::xotcl::current object].\\\n"
"Consider '[::xotcl::current object] create $m $args' instead of '[::xotcl::current object] $m $args'\"}\n"
"::xotcl::methodproperty [::xotcl::current object] unknown protected 1}\n"
"Object eval {\n"
":method public {args} {\n"
"set p [lsearch -regexp $args {^(method|alias|attribute|forward|setter)$}]\n"
"if {$p == -1} {error \"$args is not a method defining method\"}\n"
"set r [{*}:$args]\n"
"::xotcl::methodproperty [::xotcl::current object] $r protected false\n"
"return $r}\n"
":method protected {args} {\n"
"set p [lsearch -regexp $args {^(method|alias|attribute|forward|setter)$}]\n"
"if {$p == -1} {error \"$args is not a method defining command\"}\n"
"set r [{*}:$args]\n"
"::xotcl::methodproperty [::xotcl::current object] $r [::xotcl::current method] true\n"
"return $r}\n"
":protected method unknown {m args} {\n"
"if {![::xotcl::current isnext]} {\n"
"error \"[::xotcl::current object]: unable to dispatch method '$m'\"}}\n"
":protected method init args {}\n"
":protected method defaultmethod {} {::xotcl::current object}\n"
":protected method objectparameter {} {;}}\n"
"::xotcl::forward Object forward ::xotcl::forward %self -per-object\n"
"::xotcl::forward Class  forward ::xotcl::forward %self\n"
"Class protected object method __unknown {name} {}\n"
"Object public method alias {-nonleaf:switch -objscope:switch methodName cmd} {\n"
"::xotcl::alias [::xotcl::current object] -per-object $methodName \\\n"
"{*}[expr {${objscope} ? \"-objscope\" : \"\"}] \\\n"
"{*}[expr {${nonleaf} ? \"-nonleaf\" : \"\"}] \\\n"
"$cmd}\n"
"Class public method alias {-nonleaf:switch -objscope:switch methodName cmd} {\n"
"::xotcl::alias [::xotcl::current object] $methodName \\\n"
"{*}[expr {${objscope} ? \"-objscope\" : \"\"}] \\\n"
"{*}[expr {${nonleaf} ? \"-nonleaf\" : \"\"}] \\\n"
"$cmd}\n"
"Object public method setter {methodName value:optional} {\n"
"if {[info exists value]} {\n"
"::xotcl::setter [::xotcl::current object] -per-object $methodName $value} else {\n"
"::xotcl::setter [::xotcl::current object] -per-object $methodName}}\n"
"Class public method setter {methodName value:optional} {\n"
"if {[info exists value]} {\n"
"::xotcl::setter [::xotcl::current object] $methodName $value} else {\n"
"::xotcl::setter [::xotcl::current object] $methodName}}\n"
"Object create ::xotcl2::objectInfo\n"
"Object create ::xotcl2::classInfo\n"
"objectInfo eval {\n"
":alias is ::xotcl::objectproperty\n"
":public method info {obj} {\n"
"set methods [list]\n"
"foreach name [::xotcl::cmd::ObjectInfo::methods [::xotcl::current object]] {\n"
"if {$name eq \"unknown\"} continue\n"
"lappend methods $name}\n"
"return \"valid options are: [join [lsort $methods] {, }]\"}\n"
":method unknown {method obj args} {\n"
"error \"[::xotcl::current object] unknown info option \\\"$method\\\"; [$obj info info]\"}}\n"
"classInfo eval {\n"
":alias is ::xotcl::objectproperty\n"
":alias classparent ::xotcl::cmd::ObjectInfo::parent\n"
":alias classchildren ::xotcl::cmd::ObjectInfo::children\n"
":alias info [::xotcl::cmd::ObjectInfo::method objectInfo name info]\n"
":alias unknown [::xotcl::cmd::ObjectInfo::method objectInfo name info]}\n"
"foreach cmd [info command ::xotcl::cmd::ObjectInfo::*] {\n"
"::xotcl::alias ::xotcl2::objectInfo [namespace tail $cmd] $cmd\n"
"::xotcl::alias ::xotcl2::classInfo [namespace tail $cmd] $cmd}\n"
"foreach cmd [info command ::xotcl::cmd::ClassInfo::*] {\n"
"set cmdName [namespace tail $cmd]\n"
"if {$cmdName in [list \"object-mixin-of\" \"class-mixin-of\"]} continue\n"
"::xotcl::alias ::xotcl2::classInfo $cmdName $cmd}\n"
"unset cmd\n"
"Object forward info -onerror ::xotcl::infoError ::xotcl2::objectInfo %1 {%@2 %self}\n"
"Class forward  info -onerror ::xotcl::infoError ::xotcl2::classInfo %1 {%@2 %self}\n"
"proc ::xotcl::infoError msg {\n"
"regsub -all \" <object>\" $msg \"\" msg\n"
"regsub -all \" <class>\" $msg \"\" msg\n"
"regsub {\\\"} $msg \"\\\"info \" msg\n"
"error $msg \"\"}\n"
"Object method abstract {methtype -per-object:switch methname arglist} {\n"
"if {$methtype ne \"method\"} {\n"
"error \"invalid method type '$methtype', must be 'method'\"}\n"
"set body \"\n"
"if {!\\[::xotcl::current isnextcall\\]} {\n"
"error \\\"Abstract method $methname $arglist called\\\"} else {::xotcl::next}\n"
"\"\n"
"if {${per-object}} {\n"
":method -per-object $methname $arglist $body}  else {\n"
":method $methname $arglist $body}}\n"
"proc ::xotcl::unsetExitHandler {} {\n"
"proc ::xotcl::__exitHandler {} {}}\n"
"proc ::xotcl::setExitHandler {newbody} {::proc ::xotcl::__exitHandler {} $newbody}\n"
"proc ::xotcl::getExitHandler {} {::info body ::xotcl::__exitHandler}\n"
"::xotcl::unsetExitHandler\n"
"namespace export Object Class}\n"
"namespace eval ::xotcl {\n"
"::xotcl2::Class create ::xotcl::MetaSlot\n"
"::xotcl::relation ::xotcl::MetaSlot superclass ::xotcl2::Class\n"
"::xotcl::MetaSlot public method slotName {name baseObject} {\n"
"set slotParent ${baseObject}::slot\n"
"if {![::xotcl::objectproperty ${slotParent} object]} {\n"
"::xotcl2::Object create ${slotParent}}\n"
"return ${slotParent}::$name}\n"
"::xotcl::MetaSlot method createFromParameterSyntax {target -per-object:switch {-initblock \"\"} value default:optional} {\n"
"set opts [list]\n"
"set colonPos [string first : $value]\n"
"if {$colonPos == -1} {\n"
"set name $value} else {\n"
"set properties [string range $value [expr {$colonPos+1}] end]\n"
"set name [string range $value 0 [expr {$colonPos -1}]]\n"
"foreach property [split $properties ,] {\n"
"if {$property eq \"required\"} {\n"
"lappend opts -required 1} elseif {$property eq \"multivalued\"} {\n"
"lappend opts -multivalued 1} elseif {[string match type=* $property]} {\n"
"set type [string range $property 5 end]\n"
"if {![string match ::* $type]} {set type ::$type}} elseif {[string match arg=* $property]} {\n"
"set argument [string range $property 4 end]\n"
"lappend opts -arg $argument} else {\n"
"set type $property}}}\n"
"if {[info exists type]} {\n"
"lappend opts -type $type}\n"
"if {[info exists default]} {\n"
"lappend opts -default $default}\n"
"if {${per-object}} {\n"
"lappend opts -per-object true\n"
"set info ObjectInfo} else {\n"
"set info ClassInfo}\n"
":create [:slotName $name $target] {*}$opts $initblock\n"
"return [::xotcl::cmd::${info}::method $target name $name]}\n"
"::xotcl::MetaSlot create ::xotcl::Slot\n"
"::xotcl::MetaSlot create ::xotcl::ObjectParameterSlot\n"
"::xotcl::relation ::xotcl::ObjectParameterSlot superclass ::xotcl::Slot\n"
"::xotcl::MetaSlot create ::xotcl::MethodParameterSlot\n"
"::xotcl::relation ::xotcl::MethodParameterSlot superclass ::xotcl::Slot\n"
"::xotcl::MethodParameterSlot create ::xotcl::methodParameterSlot\n"
"proc createBootstrapAttributeSlots {class definitions} {\n"
"foreach att $definitions {\n"
"if {[llength $att]>1} {foreach {att default} $att break}\n"
"set slotObj [::xotcl::ObjectParameterSlot slotName $att $class]\n"
"::xotcl::ObjectParameterSlot create $slotObj\n"
"if {[info exists default]} {\n"
"::xotcl::setvar $slotObj default $default\n"
"unset default}\n"
"::xotcl::setter $class $att}\n"
"foreach att $definitions {\n"
"if {[llength $att]>1} {foreach {att default} $att break}\n"
"if {[info exists default]} {\n"
"foreach i [::xotcl::cmd::ClassInfo::instances $class] {\n"
"if {![$i exists $att]} {\n"
"if {[string match {*\\[*\\]*} $default]} {\n"
"set value [::xotcl::dispatch $i -objscope ::eval subst $default]} else {\n"
"set value $default}\n"
"::xotcl::setvar $i $att $value}}\n"
"unset default}}\n"
"$class __invalidateobjectparameter}\n"
"createBootstrapAttributeSlots ::xotcl::Slot {\n"
"{name}\n"
"{multivalued false}\n"
"{required false}\n"
"default\n"
"type}\n"
"createBootstrapAttributeSlots ::xotcl::ObjectParameterSlot {\n"
"{name \"[namespace tail [::xotcl::current object]]\"}\n"
"{methodname}\n"
"{domain \"[lindex [regexp -inline {^(.*)::slot::[^:]+$} [::xotcl::current object]] 1]\"}\n"
"{defaultmethods {get assign}}\n"
"{manager \"[::xotcl::current object]\"}\n"
"{per-object false}}\n"
"::xotcl::alias ::xotcl::ObjectParameterSlot get ::xotcl::setvar\n"
"::xotcl::alias ::xotcl::ObjectParameterSlot assign ::xotcl::setvar\n"
"::xotcl::ObjectParameterSlot public method add {obj prop value {pos 0}} {\n"
"if {![set :multivalued]} {\n"
"error \"Property $prop of [set :domain]->$obj ist not multivalued\"}\n"
"if {[$obj exists $prop]} {\n"
"::xotcl::setvar $obj $prop [linsert [::xotcl::setvar $obj $prop] $pos $value]} else {\n"
"::xotcl::setvar $obj $prop [list $value]}}\n"
"::xotcl::ObjectParameterSlot public method delete {-nocomplain:switch obj prop value} {\n"
"set old [::xotcl::setvar $obj $prop]\n"
"set p [lsearch -glob $old $value]\n"
"if {$p>-1} {::xotcl::setvar $obj $prop [lreplace $old $p $p]} else {\n"
"error \"$value is not a $prop of $obj (valid are: $old)\"}}\n"
"::xotcl::ObjectParameterSlot method unknown {method args} {\n"
"set methods [list]\n"
"foreach m [:info callable] {\n"
"if {[::xotcl2::Object info callable $m] ne \"\"} continue\n"
"if {[string match __* $m]} continue\n"
"lappend methods $m}\n"
"error \"Method '$method' unknown for slot [::xotcl::current object]; valid are: {[lsort $methods]}\"}\n"
"::xotcl::ObjectParameterSlot public method destroy {} {\n"
"if {${:domain} ne \"\" && [::xotcl::objectproperty ${:domain} class]} {\n"
"${:domain} __invalidateobjectparameter}\n"
"next}\n"
"::xotcl::ObjectParameterSlot protected method init {args} {\n"
"if {${:domain} eq \"\"} {\n"
"set :domain [::xotcl::current callingobject]}\n"
"if {${:domain} ne \"\"} {\n"
"if {![info exists :methodname]} {\n"
"set :methodname ${:name}}\n"
"if {[::xotcl::objectproperty ${:domain} class]} {\n"
"${:domain} __invalidateobjectparameter}\n"
"if {${:per-object} && [info exists :default] } {\n"
"::xotcl::setvar ${:domain} ${:name} ${:default}}\n"
"set cl [expr {${:per-object} ? \"Object\" : \"Class\"}]\n"
"::xotcl::forward ${:domain} ${:name} \\\n"
"${:manager} \\\n"
"[list %1 [${:manager} defaultmethods]] %self \\\n"
"${:methodname}}}\n"
"::xotcl::MetaSlot __invalidateobjectparameter\n"
"::xotcl::ObjectParameterSlot method toParameterSyntax {{name:substdefault ${:name}}} {\n"
"set objparamdefinition $name\n"
"set methodparamdefinition \"\"\n"
"set objopts [list]\n"
"set methodopts [list]\n"
"set type \"\"\n"
"if {[info exists :required] && ${:required}} {\n"
"lappend objopts required\n"
"lappend methodopts required}\n"
"if {[info exists :type]} {\n"
"if {[string match ::* ${:type}]} {\n"
"set type [expr {[::xotcl::objectproperty ${:type} metaclass] ? \"class\" : \"object\"}]\n"
"lappend objopts type=${:type}\n"
"lappend methodopts type=${:type}} else {\n"
"set type ${:type}}}\n"
"if {[info exists :multivalued] && ${:multivalued}} {\n"
"if {!([info exists :type] && ${:type} eq \"relation\")} {\n"
"lappend objopts multivalued} else {}}\n"
"if {[info exists :arg]} {\n"
"set prefix [expr {$type eq \"object\" || $type eq \"class\" ? \"type\" : \"arg\"}]\n"
"lappend objopts $prefix=${:arg}\n"
"lappend methodopts $prefix=${:arg}}\n"
"if {[info exists :default]} {\n"
"set arg ${:default}\n"
"if {[string match {*\\[*\\]*} $arg]} {\n"
"lappend objopts substdefault}} elseif {[info exists :initcmd]} {\n"
"set arg ${:initcmd}\n"
"lappend objopts initcmd}\n"
"if {[info exists :methodname]} {\n"
"if {${:methodname} ne ${:name}} {\n"
"lappend objopts arg=${:methodname}\n"
"lappend methodopts arg=${:methodname}}}\n"
"if {$type ne \"\"} {\n"
"set objopts [linsert $objopts 0 $type]\n"
"set methodopts [linsert $methodopts 0 $type]}\n"
"lappend objopts slot=[::xotcl::current object]\n"
"if {[llength $objopts] > 0} {\n"
"append objparamdefinition :[join $objopts ,]}\n"
"if {[llength $methodopts] > 0} {\n"
"set methodparamdefinition [join $methodopts ,]}\n"
"if {[info exists arg]} {\n"
"lappend objparamdefinition $arg}\n"
"return [list oparam $objparamdefinition mparam $methodparamdefinition]}\n"
"proc ::xotcl::parametersFromSlots {obj} {\n"
"set parameterdefinitions [list]\n"
"foreach slot [::xotcl2::objectInfo slotobjects $obj] {\n"
"if {[::xotcl::objectproperty $obj type ::xotcl::Object] &&\n"
"([$slot name] eq \"mixin\" || [$slot name] eq \"filter\")} continue\n"
"array set \"\" [$slot toParameterSyntax]\n"
"lappend parameterdefinitions -$(oparam)}\n"
"return $parameterdefinitions}\n"
"::xotcl2::Object protected method objectparameter {} {\n"
"set parameterdefinitions [::xotcl::parametersFromSlots [::xotcl::current object]]\n"
"if {[::xotcl::objectproperty [::xotcl::current object] class]} {\n"
"lappend parameterdefinitions -parameter:method,optional}\n"
"lappend parameterdefinitions \\\n"
"-noinit:method,optional,noarg \\\n"
"-volatile:method,optional,noarg \\\n"
"arg:initcmd,optional\n"
"return $parameterdefinitions}\n"
"::xotcl::MetaSlot create ::xotcl::RelationSlot\n"
"createBootstrapAttributeSlots ::xotcl::RelationSlot {\n"
"{multivalued true}\n"
"{type relation}\n"
"{elementtype ::xotcl2::Class}}\n"
"::xotcl::relation ::xotcl::RelationSlot superclass ::xotcl::ObjectParameterSlot\n"
"::xotcl::alias ::xotcl::RelationSlot assign ::xotcl::relation\n"
"::xotcl::RelationSlot protected method init {} {\n"
"if {${:type} ne \"relation\"} {\n"
"error \"RelationSlot requires type == \\\"relation\\\"\"}\n"
"next}\n"
"::xotcl::RelationSlot protected method delete_value {obj prop old value} {\n"
"if {[string first * $value] > -1 || [string first \\[ $value] > -1} {\n"
"if {${:elementtype} ne \"\" && ![string match ::* $value]} {\n"
"set value ::$value}\n"
"return [lsearch -all -not -glob -inline $old $value]} elseif {${:elementtype} ne \"\"} {\n"
"if {[string first :: $value] == -1} {\n"
"if {![::xotcl::objectproperty $value object]} {\n"
"error \"$value does not appear to be an object\"}\n"
"set value [::xotcl::dispatch $value -objscope ::xotcl::current object]}\n"
"if {![::xotcl::objectproperty ${:elementtype} class]} {\n"
"error \"$value does not appear to be of type ${:elementtype}\"}}\n"
"set p [lsearch -exact $old $value]\n"
"if {$p > -1} {\n"
"return [lreplace $old $p $p]} else {\n"
"error \"$value is not a $prop of $obj (valid are: $old)\"}}\n"
"::xotcl::RelationSlot public method delete {-nocomplain:switch obj prop value} {\n"
"$obj $prop [:delete_value $obj $prop [$obj info $prop] $value]}\n"
"::xotcl::RelationSlot public method get {obj prop} {\n"
"::xotcl::relation $obj $prop}\n"
"::xotcl::RelationSlot public method add {obj prop value {pos 0}} {\n"
"if {![set :multivalued]} {\n"
"error \"Property $prop of ${:domain}->$obj ist not multivalued\"}\n"
"set oldSetting [::xotcl::relation $obj $prop]\n"
"uplevel [list ::xotcl::relation $obj $prop [linsert $oldSetting $pos $value]]}\n"
"::xotcl::RelationSlot public method delete {-nocomplain:switch obj prop value} {\n"
"uplevel [list ::xotcl::relation $obj $prop [:delete_value $obj $prop [::xotcl::relation $obj $prop] $value]]}\n"
"proc ::xotcl::register_system_slots {os} {\n"
"${os}::Object alloc ${os}::Class::slot\n"
"${os}::Object alloc ${os}::Object::slot\n"
"::xotcl::RelationSlot create ${os}::Class::slot::superclass\n"
"::xotcl::alias           ${os}::Class::slot::superclass assign ::xotcl::relation\n"
"::xotcl::RelationSlot create ${os}::Object::slot::class -multivalued false\n"
"::xotcl::alias           ${os}::Object::slot::class assign ::xotcl::relation\n"
"::xotcl::RelationSlot create ${os}::Object::slot::mixin -methodname object-mixin\n"
"::xotcl::RelationSlot create ${os}::Object::slot::filter -elementtype \"\"\n"
"::xotcl::RelationSlot create ${os}::Class::slot::mixin -methodname class-mixin\n"
"::xotcl::RelationSlot create ${os}::Class::slot::filter -elementtype \"\" \\\n"
"-methodname class-filter\n"
"::xotcl::RelationSlot create ${os}::Class::slot::object-mixin\n"
"::xotcl::RelationSlot create ${os}::Class::slot::object-filter -elementtype \"\"}\n"
"::xotcl::register_system_slots ::xotcl2\n"
"proc ::xotcl::register_system_slots {} {}\n"
"::xotcl::MetaSlot __invalidateobjectparameter\n"
"::xotcl::MetaSlot create ::xotcl::Attribute -superclass ::xotcl::ObjectParameterSlot\n"
"createBootstrapAttributeSlots ::xotcl::Attribute {\n"
"{value_check once}\n"
"incremental\n"
"initcmd\n"
"valuecmd\n"
"valuechangedcmd\n"
"arg}\n"
"::xotcl::Attribute method __default_from_cmd {obj cmd var sub op} {\n"
"$obj trace remove variable $var $op [list [::xotcl::current object] [::xotcl::current method] $obj $cmd]\n"
"::xotcl::setvar $obj $var [$obj eval $cmd]}\n"
"::xotcl::Attribute method __value_from_cmd {obj cmd var sub op} {\n"
"::xotcl::setvar $obj $var [$obj eval $cmd]}\n"
"::xotcl::Attribute method __value_changed_cmd {obj cmd var sub op} {\n"
"eval $cmd}\n"
"::xotcl::Attribute protected method init {} {\n"
"next ;# do first ordinary slot initialization\n"
"set __initcmd \"\"\n"
"if {[:exists default]} {} elseif [:exists initcmd] {\n"
"append __initcmd \":trace add variable [list ${:name}] read \\\n"
"\\[list [::xotcl::current object] __default_from_cmd \\[::xotcl::current object\\] [list [set :initcmd]]\\]\\n\"} elseif [:exists valuecmd] {\n"
"append __initcmd \":trace add variable [list ${:name}] read \\\n"
"\\[list [::xotcl::current object] __value_from_cmd \\[::xotcl::current object\\] [list [set :valuecmd]]\\]\"}\n"
"array set \"\" [:toParameterSyntax ${:name}]\n"
"if {$(mparam) ne \"\"} {\n"
"if {[info exists :multivalued] && ${:multivalued}} {\n"
":method assign [list obj var value:$(mparam),multivalued,slot=[::xotcl::current object]] {::xotcl::setvar $obj $var $value}\n"
":method add [list obj prop value:$(mparam),slot=[::xotcl::current object] {pos 0}] {next}} else {\n"
":method assign [list obj var value:$(mparam),slot=[::xotcl::current object]] {::xotcl::setvar $obj $var $value}}}\n"
"if {[:exists valuechangedcmd]} {\n"
"append __initcmd \":trace add variable [list ${:name}] write \\\n"
"\\[list [::xotcl::current object] __value_changed_cmd \\[::xotcl::current object\\] [list [set :valuechangedcmd]]\\]\"}\n"
"if {$__initcmd ne \"\"} {\n"
"set :initcmd $__initcmd}}\n"
"::xotcl2::Class create ::xotcl::Attribute::Optimizer {\n"
":method method args  {::xotcl::next; :optimize}\n"
":method forward args {::xotcl::next; :optimize}\n"
":protected method init args {::xotcl::next; :optimize}\n"
":public method optimize {} {\n"
"if {![info exists :methodname]} {return}\n"
"set object [expr {${:per-object} ? {object} : {}}]\n"
"if {${:per-object}} {\n"
"set perObject -per-object\n"
"set infokind Object} else {\n"
"set perObject \"\"\n"
"set infokind Class}\n"
"if {[::xotcl::cmd::${infokind}Info::method ${:domain} name ${:name}] ne \"\"} {\n"
"::xotcl::forward ${:domain} {*}$perObject ${:name} \\\n"
"${:manager} \\\n"
"[list %1 [${:manager} defaultmethods]] %self \\\n"
"${:methodname}}\n"
"if {[info exists :incremental] && ${:incremental}} return\n"
"if {[set :defaultmethods] ne {get assign}} return\n"
"set assignInfo [:info callable -which assign]\n"
"if {$assignInfo ne \"::xotcl::ObjectParameterSlot alias assign ::xotcl::setvar\" &&\n"
"[lindex $assignInfo {end 0}] ne \"::xotcl::setvar\" } return\n"
"if {[:info callable -which get]    ne \"::xotcl::ObjectParameterSlot alias get ::xotcl::setvar\"} return\n"
"array set \"\" [:toParameterSyntax ${:name}]\n"
"if {$(mparam) ne \"\"} {\n"
"set setterParam [lindex $(oparam) 0]} else {\n"
"set setterParam ${:name}}\n"
"::xotcl::setter ${:domain} {*}$perObject $setterParam}}\n"
"::xotcl::Attribute mixin add ::xotcl::Attribute::Optimizer\n"
"::xotcl2::Class method attribute {spec {-slotclass ::xotcl::Attribute} {initblock \"\"}} {\n"
"$slotclass createFromParameterSyntax [::xotcl::current object] -initblock $initblock {*}$spec}\n"
"::xotcl2::Object method attribute {spec {-slotclass ::xotcl::Attribute} {initblock \"\"}} {\n"
"$slotclass createFromParameterSyntax [::xotcl::current object] -per-object -initblock $initblock {*}$spec}\n"
"::xotcl2::Class public method parameter arglist {\n"
"foreach arg $arglist {\n"
"::xotcl::Attribute createFromParameterSyntax [::xotcl::current object] {*}$arg}}\n"
"proc createBootstrapAttributeSlots {} {}\n"
"::xotcl::Slot method type=hasmixin {name value arg} {\n"
"if {![::xotcl::objectproperty $value hasmixin $arg]} {\n"
"error \"expected object with mixin $arg but got \\\"$value\\\" for parameter $name\"}\n"
"return $value}\n"
"::xotcl::Slot method type=baseclass {name value} {\n"
"if {![::xotcl::objectproperty $value baseclass]} {\n"
"error \"expected baseclass but got \\\"$value\\\" for parameter $name\"}\n"
"return $value}\n"
"::xotcl::Slot method type=metaclass {name value} {\n"
"if {![::xotcl::objectproperty $value metaclass]} {\n"
"error \"expected metaclass but got \\\"$value\\\" for parameter $name\"}\n"
"return $value}}\n"
"::xotcl2::Class create ::xotcl::ScopedNew -superclass ::xotcl2::Class {\n"
":attribute {withclass ::xotcl2::Object}\n"
":attribute container\n"
":protected method init {} {\n"
":public method new {-childof args} {\n"
"::xotcl::importvar [::xotcl::current class] {container object} withclass\n"
"if {![::xotcl::objectproperty $object object]} {\n"
"$withclass create $object}\n"
"eval ::xotcl::next -childof $object $args}}}\n"
"::xotcl2::Object public method contains {\n"
"{-withnew:boolean true}\n"
"-object\n"
"{-class ::xotcl2::Object}\n"
"cmds} {\n"
"if {![info exists object]} {set object [::xotcl::current object]}\n"
"if {![::xotcl::objectproperty $object object]} {$class create $object}\n"
"$object requireNamespace\n"
"if {$withnew} {\n"
"set m [::xotcl::ScopedNew new -volatile \\\n"
"-container $object -withclass $class]\n"
"::xotcl2::Class mixin add $m end\n"
"if {[::xotcl::objectproperty ::xotcl::Class class]} {::xotcl::Class instmixin add $m end}\n"
"namespace eval $object $cmds\n"
"::xotcl2::Class mixin delete $m\n"
"if {[::xotcl::objectproperty ::xotcl::Class class]} {::xotcl::Class instmixin delete $m}} else {\n"
"namespace eval $object $cmds}}\n"
"::xotcl2::Class forward slots %self contains \\\n"
"-object {%::xotcl::dispatch [::xotcl::current object] -objscope ::subst [::xotcl::current object]::slot}\n"
"::xotcl2::Class create ::xotcl::CopyHandler {\n"
":attribute {targetList \"\"}\n"
":attribute {dest \"\"}\n"
":attribute objLength\n"
":method makeTargetList {t} {\n"
"lappend :targetList $t\n"
"if {[::xotcl::objectproperty $t object]} {\n"
"if {[$t info hasnamespace]} {\n"
"set children [$t info children]} else {\n"
"return}}\n"
"foreach c [namespace children $t] {\n"
"if {![::xotcl::objectproperty $c object]} {\n"
"lappend children [namespace children $t]}}\n"
"foreach c $children {\n"
":makeTargetList $c}}\n"
":method copyNSVarsAndCmds {orig dest} {\n"
"::xotcl::namespace_copyvars $orig $dest\n"
"::xotcl::namespace_copycmds $orig $dest}\n"
":method getDest origin {\n"
"set tail [string range $origin [set :objLength] end]\n"
"return ::[string trimleft [set :dest]$tail :]}\n"
":method copyTargets {} {\n"
"foreach origin [set :targetList] {\n"
"set dest [:getDest $origin]\n"
"if {[::xotcl::objectproperty $origin object]} {\n"
"if {[::xotcl::objectproperty $origin class]} {\n"
"set cl [[$origin info class] create $dest -noinit]\n"
"set obj $cl\n"
"$cl superclass [$origin info superclass]\n"
"::xotcl::assertion $cl class-invar [::xotcl::assertion $origin class-invar]\n"
"::xotcl::relation $cl class-filter [::xotcl::relation $origin class-filter]\n"
"::xotcl::relation $cl class-mixin [::xotcl::relation $origin class-mixin]\n"
":copyNSVarsAndCmds ::xotcl::classes$origin ::xotcl::classes$dest} else {\n"
"set obj [[$origin info class] create $dest -noinit]}\n"
"::xotcl::assertion $obj check [::xotcl::assertion $origin check]\n"
"::xotcl::assertion $obj object-invar [::xotcl::assertion $origin object-invar]\n"
"::xotcl::relation $obj object-filter [::xotcl::relation $origin object-filter]\n"
"::xotcl::relation $obj object-mixin [::xotcl::relation $origin object-mixin]\n"
"if {[$origin info hasnamespace]} {\n"
"$obj requireNamespace}} else {\n"
"namespace eval $dest {}}\n"
":copyNSVarsAndCmds $origin $dest\n"
"foreach i [::xotcl::cmd::ObjectInfo::forward $origin] {\n"
"eval [concat ::xotcl::forward $dest -per-object $i [::xotcl::cmd::ObjectInfo::forward $origin -definition $i]]}\n"
"if {[::xotcl::objectproperty $origin class]} {\n"
"foreach i [::xotcl::cmd::ClassInfo::forward $origin] {\n"
"eval [concat ::xotcl::forward $dest $i [::xotcl::cmd::ClassInfo::forward $origin -definition $i]]}}\n"
"set traces [list]\n"
"foreach var [$origin info vars] {\n"
"set cmds [::xotcl::dispatch $origin -objscope ::trace info variable $var]\n"
"if {$cmds ne \"\"} {\n"
"foreach cmd $cmds {\n"
"foreach {op def} $cmd break\n"
"if {[lindex $def 0] eq $origin} {\n"
"set def [concat $dest [lrange $def 1 end]]}\n"
"$dest trace add variable $var $op $def}}}}\n"
"foreach origin [set :targetList] {\n"
"if {[::xotcl::objectproperty $origin class]} {\n"
"set dest [:getDest $origin]\n"
"foreach oldslot [$origin info slots] {\n"
"set newslot [::xotcl::Slot slotName [namespace tail $oldslot] $dest]\n"
"if {[$oldslot domain] eq $origin}   {$newslot domain $cl}\n"
"if {[$oldslot manager] eq $oldslot} {$newslot manager $newslot}}}}}\n"
":public method copy {obj dest} {\n"
"set :objLength [string length $obj]\n"
"set :dest $dest\n"
":makeTargetList $obj\n"
":copyTargets}}\n"
"::xotcl2::Object public method copy newName {\n"
"if {[string compare [string trimleft $newName :] [string trimleft [::xotcl::current object] :]]} {\n"
"[::xotcl::CopyHandler new -volatile] copy [::xotcl::current object] $newName}}\n"
"::xotcl2::Object public method move newName {\n"
"if {[string trimleft $newName :] ne [string trimleft [::xotcl::current object] :]} {\n"
"if {$newName ne \"\"} {\n"
":copy $newName}\n"
"if {[::xotcl::objectproperty [::xotcl::current object] class] && $newName ne \"\"} {\n"
"foreach subclass [:info subclass] {\n"
"set scl [$subclass info superclass]\n"
"if {[set index [lsearch -exact $scl [::xotcl::current object]]] != -1} {\n"
"set scl [lreplace $scl $index $index $newName]\n"
"$subclass superclass $scl}}	}\n"
":destroy}}\n"
"::xotcl2::Object create ::xotcl::@ {\n"
":method unknown args {}}\n"
"namespace eval ::xotcl {\n"
"namespace export @ Attribute current\n"
"if {![info exists ::env(HOME)]} {set ::env(HOME) /root}\n"
"set ::xotcl::confdir ~/.xotcl\n"
"set ::xotcl::logdir $::xotcl::confdir/log\n"
"proc tmpdir {} {\n"
"foreach e [list TMPDIR TEMP TMP] {\n"
"if {[info exists ::env($e)] \\\n"
"&& [file isdirectory $::env($e)] \\\n"
"&& [file writable $::env($e)]} {\n"
"return $::env($e)}}\n"
"if {$::tcl_platform(platform) eq \"windows\"} {\n"
"foreach d [list \"C:\\\\TEMP\" \"C:\\\\TMP\" \"\\\\TEMP\" \"\\\\TMP\"] {\n"
"if {[file isdirectory $d] && [file writable $d]} {\n"
"return $d}}}\n"
"return /tmp}\n"
"proc use {version} {\n"
"set callingNs [uplevel {namespace current}]\n"
"switch -exact $version {\n"
"xotcl1 {\n"
"package require xotcl1\n"
"if {$callingNs ne \"::xotcl\"} {uplevel {namespace import -force ::xotcl::*}}}\n"
"default {\n"
"if {$callingNs ne \"::xotcl\"} {uplevel {namespace import -force ::xotcl::*}}\n"
"if {$callingNs ne \"::xotcl2\"} {uplevel {namespace import -force ::xotcl2::*}}}}}\n"
"unset bootstrap}\n"
"";

