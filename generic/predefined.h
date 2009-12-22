static char cmd[] = 
"namespace eval ::xotcl {\n"
"set bootstrap 1}\n"
"namespace eval xotcl2 {\n"
"namespace path ::xotcl\n"
"::xotcl::createobjectsystem ::xotcl2::Object ::xotcl2::Class\n"
"foreach cmd [info command ::xotcl::cmd::Object::*] {\n"
"set cmdName [namespace tail $cmd]\n"
"if {$cmdName in [list \"instvar\" \"object-method\"]} continue\n"
"::xotcl::alias Object $cmdName $cmd}\n"
"foreach cmd [info command ::xotcl::cmd::Class::*] {\n"
"set cmdName [namespace tail $cmd]\n"
"if {$cmdName in [list \"class-method\"]} continue\n"
"::xotcl::alias Class $cmdName $cmd}\n"
"foreach cmd [list __next cleanup  noinit residualargs] {\n"
"::xotcl::methodproperty Object $cmd protected 1}\n"
"foreach cmd [list recreate] {\n"
"::xotcl::methodproperty Class $cmd protected 1}\n"
"::xotcl::methodproperty Object destroy static true\n"
"::xotcl::methodproperty Class  alloc   static true\n"
"::xotcl::methodproperty Class  dealloc static true\n"
"::xotcl::methodproperty Class  create  static true\n"
"::xotcl::dispatch Class ::xotcl::cmd::Class::class-method method {\n"
"-per-object:switch -public:switch -protected:switch\n"
"name arguments body -precondition -postcondition} {\n"
"set conditions [list]\n"
"if {[info exists precondition]}  {lappend conditions -precondition  $precondition}\n"
"if {[info exists postcondition]} {lappend conditions -postcondition $postcondition}\n"
"if {${per-object}} {\n"
"set cls Object\n"
"set prefix object} else {\n"
"set cls Class\n"
"set prefix class}\n"
"::xotcl::dispatch [self] ::xotcl::cmd::${cls}::$prefix-method \\\n"
"$name $arguments $body {*}$conditions\n"
"if {$protected} {::xotcl::methodproperty [self] $name protected true}}\n"
"::xotcl::dispatch Object ::xotcl::cmd::Class::class-method method {\n"
"-public:switch -protected:switch\n"
"name arguments body -precondition -postcondition} {\n"
"set conditions [list]\n"
"if {[info exists precondition]}  {lappend conditions -precondition  $precondition}\n"
"if {[info exists postcondition]} {lappend conditions -postcondition $postcondition}\n"
"::xotcl::dispatch [self] ::xotcl::cmd::Object::object-method \\\n"
"$name $arguments $body {*}$conditions\n"
"if {$protected} {::xotcl::methodproperty [self] $name -per-object protected true}}\n"
"Class method unknown {args} {\n"
"puts stderr \"use '[self] create $args', not '[self] $args'\"\n"
"eval my create $args}\n"
"Object method unknown {m args} {\n"
"if {![self isnext]} {\n"
"error \"[self]: unable to dispatch method '$m'\"}}\n"
"Object method -protected init args {}\n"
"Object method defaultmethod {} {::xotcl::self}\n"
"Object method -protected objectparameter {} {;}\n"
"Class method -per-object __unknown {name} {}\n"
"Object method -public alias {-objscope:switch -protected:switch methodName cmd} {\n"
"::xotcl::alias [self] $methodName \\\n"
"{*}[expr {${objscope} ? \"-objscope\" : \"\"}] \\\n"
"{*}[expr {${protected} ? \"-protected\" : \"\"}] \\\n"
"$cmd}\n"
"Class method -public alias {-objscope:switch -per-object:switch -protected:switch methodName cmd} {\n"
"::xotcl::alias [self] $methodName \\\n"
"{*}[expr {${objscope} ? \"-objscope\" : \"\"}] \\\n"
"{*}[expr {${per-object} ? \"-per-object\" : \"\"}] \\\n"
"{*}[expr {${protected} ? \"-protected\" : \"\"}] \\\n"
"$cmd}\n"
"Object create ::xotcl2::objectInfo\n"
"Object create ::xotcl2::classInfo\n"
"::xotcl::dispatch objectInfo -objscope ::eval {\n"
".alias is ::xotcl::is\n"
".method -public info {obj} {\n"
"set methods [list]\n"
"foreach name [::xotcl::cmd::ObjectInfo::methods [self]] {\n"
"if {$name eq \"unknown\"} continue\n"
"lappend methods $name}\n"
"return \"valid options are: [join [lsort $methods] {, }]\"}\n"
".method unknown {method obj args} {\n"
"error \"[::xotcl::self] unknown info option \\\"$method\\\"; [$obj info info]\"}}\n"
"::xotcl::dispatch classInfo -objscope ::eval {\n"
".alias is ::xotcl::is\n"
".alias classparent ::xotcl::cmd::ObjectInfo::parent\n"
".alias classchildren ::xotcl::cmd::ObjectInfo::children\n"
".alias info [::xotcl::cmd::ObjectInfo::method objectInfo name info]\n"
".alias unknown [::xotcl::cmd::ObjectInfo::method objectInfo name info]}\n"
"foreach cmd [info command ::xotcl::cmd::ObjectInfo::*] {\n"
"::xotcl::alias ::xotcl2::objectInfo [namespace tail $cmd] $cmd\n"
"::xotcl::alias ::xotcl2::classInfo [namespace tail $cmd] $cmd}\n"
"foreach cmd [info command ::xotcl::cmd::ClassInfo::*] {\n"
"set cmdName [namespace tail $cmd]\n"
"if {$cmdName in [list \"instfilter\" \"instforward\" \"instmixin\" \"instmixinguard\" \"instparams\"]} continue\n"
"::xotcl::alias ::xotcl2::classInfo $cmdName $cmd}\n"
"unset cmd\n"
"Object forward info -onerror ::xotcl::infoError ::xotcl2::objectInfo %1 {%@2 %self}\n"
"Class forward  info -onerror ::xotcl::infoError ::xotcl2::classInfo %1 {%@2 %self}\n"
"::xotcl::dispatch ::xotcl2::classInfo ::xotcl::cmd::Object::forward \\\n"
"\"-per-object\" ::xotcl2::objectInfo {%@2 %1}\n"
"proc ::xotcl::infoError msg {\n"
"regsub -all \" <object>\" $msg \"\" msg\n"
"regsub -all \" <class>\" $msg \"\" msg\n"
"regsub {\\\"} $msg \"\\\"info \" msg\n"
"error $msg \"\"}\n"
"Object method abstract {methtype -per-object:switch methname arglist} {\n"
"if {$methtype ne \"method\"} {\n"
"error \"invalid method type '$methtype', must be 'method'\"}\n"
"set body \"\n"
"if {!\\[::xotcl::self isnextcall\\]} {\n"
"error \\\"Abstract method $methname $arglist called\\\"} else {::xotcl::next}\n"
"\"\n"
"if {${per-object}} {\n"
".method -per-object $methname $arglist $body}  else {\n"
".method $methname $arglist $body}}\n"
"proc ::xotcl::unsetExitHandler {} {\n"
"proc ::xotcl::__exitHandler {} {}}\n"
"proc ::xotcl::setExitHandler {newbody} {proc ::xotcl::__exitHandler {} $newbody}\n"
"proc ::xotcl::getExitHandler {} {::info body ::xotcl::__exitHandler}\n"
"::xotcl::unsetExitHandler\n"
"namespace export Object Class}\n"
"::xotcl2::Class create ::xotcl::MetaSlot\n"
"::xotcl::relation ::xotcl::MetaSlot superclass ::xotcl2::Class\n"
"::xotcl::MetaSlot method -public new args {\n"
"set slotobject [::xotcl::self callingobject]::slot\n"
"if {![::xotcl::is $slotobject object]} {::xotcls::Object create $slotobject}\n"
"eval next -childof $slotobject $args}\n"
"::xotcl::MetaSlot create ::xotcl::Slot\n"
"::xotcl::MetaSlot __invalidateobjectparameter\n"
"proc ::xotcl::parametersFromSlots {obj} {\n"
"set parameterdefinitions [list]\n"
"set slots [::xotcl2::objectInfo slotobjects $obj]\n"
"foreach slot $slots {\n"
"if {[::xotcl::is $obj type ::xotcl::Object] &&\n"
"([$slot name] eq \"mixin\" || [$slot name] eq \"filter\")} continue\n"
"set parameterdefinition \"-[namespace tail $slot]\"\n"
"set opts [list]\n"
"if {[$slot exists required] && [$slot required]} {\n"
"lappend opts required}\n"
"if {[$slot exists type]} {\n"
"lappend opts [$slot type]}\n"
"if {[$slot exists default]} {\n"
"set arg [::xotcl::setinstvar $slot default]\n"
"if {[string match {*\\[*\\]*} $arg]} {\n"
"lappend opts substdefault}} elseif {[$slot exists initcmd]} {\n"
"set arg [::xotcl::setinstvar $slot initcmd]\n"
"lappend opts initcmd}\n"
"if {[llength $opts] > 0} {\n"
"append parameterdefinition :[join $opts ,]}\n"
"if {[info exists arg]} {\n"
"lappend parameterdefinition $arg\n"
"unset arg}\n"
"lappend parameterdefinitions $parameterdefinition}\n"
"return $parameterdefinitions}\n"
"::xotcl2::Object method -protected objectparameter {} {\n"
"set parameterdefinitions [::xotcl::parametersFromSlots [self]]\n"
"if {[::xotcl::is [self] class]} {\n"
"lappend parameterdefinitions -parameter:method,optional}\n"
"lappend parameterdefinitions \\\n"
"-noinit:method,optional,noarg \\\n"
"-volatile:method,optional,noarg \\\n"
"arg:initcmd,optional\n"
"return $parameterdefinitions}\n"
"::xotcl2::Class create ::xotcl2::ParameterType\n"
"foreach cmd [info command ::xotcl::cmd::ParameterType::*] {\n"
"::xotcl::alias ::xotcl2::ParameterType [namespace tail $cmd] $cmd}\n"
"::xotcl2::ParameterType create ::xotcl2::parameterType\n"
"proc createBootstrapAttributeSlots {class definitions} {\n"
"if {![::xotcl::is ${class}::slot object]} {\n"
"::xotcl2::Object create ${class}::slot}\n"
"foreach att $definitions {\n"
"if {[llength $att]>1} {foreach {att default} $att break}\n"
"::xotcl::Slot create ${class}::slot::$att\n"
"if {[info exists default]} {\n"
"::xotcl::setinstvar ${class}::slot::$att default $default\n"
"unset default}\n"
"$class setter $att}\n"
"foreach att $definitions {\n"
"if {[llength $att]>1} {foreach {att default} $att break}\n"
"if {[info exists default]} {\n"
"foreach i [::xotcl::cmd::ClassInfo::instances $class] {\n"
"if {![$i exists $att]} {\n"
"if {[string match {*[*]*} $default]} {\n"
"set default [::xotcl::dispatch $i -objscope ::eval subst $default]}\n"
"::xotcl::setinstvar $i $att $default}}\n"
"unset default}}\n"
"$class __invalidateobjectparameter}\n"
"createBootstrapAttributeSlots ::xotcl::Slot {\n"
"{name \"[namespace tail [::xotcl::self]]\"}\n"
"{domain \"[lindex [regexp -inline {^(.*)::slot::[^:]+$} [::xotcl::self]] 1]\"}\n"
"{defaultmethods {get assign}}\n"
"{manager \"[::xotcl::self]\"}\n"
"{multivalued false}\n"
"{per-object false}\n"
"{forward-per-object}\n"
"{required false}\n"
"default\n"
"type}\n"
"::xotcl::alias ::xotcl::Slot get ::xotcl::setinstvar\n"
"::xotcl::alias ::xotcl::Slot assign ::xotcl::setinstvar\n"
"::xotcl::Slot method -public add {obj prop value {pos 0}} {\n"
"if {![set .multivalued]} {\n"
"error \"Property $prop of [set .domain]->$obj ist not multivalued\"}\n"
"if {[$obj exists $prop]} {\n"
"::xotcl::setinstvar $obj $prop [linsert [::xotcl::setinstvar $obj $prop] $pos $value]} else {\n"
"::xotcl::setinstvar $obj $prop [list $value]}}\n"
"::xotcl::Slot method -public delete {-nocomplain:switch obj prop value} {\n"
"set old [::xotcl::setinstvar $obj $prop]\n"
"set p [lsearch -glob $old $value]\n"
"if {$p>-1} {::xotcl::setinstvar $obj $prop [lreplace $old $p $p]} else {\n"
"error \"$value is not a $prop of $obj (valid are: $old)\"}}\n"
"::xotcl::Slot method unknown {method args} {\n"
"set methods [list]\n"
"foreach m [.info callable] {\n"
"if {[::xotcl2::Object info callable $m] ne \"\"} continue\n"
"if {[string match __* $m]} continue\n"
"lappend methods $m}\n"
"error \"Method '$method' unknown for slot [::xotcl::self]; valid are: {[lsort $methods]]}\"}\n"
"::xotcl::Slot method -public destroy {} {\n"
"if {${.domain} ne \"\"} {\n"
"${.domain} __invalidateobjectparameter}\n"
"next}\n"
"::xotcl::Slot method init {args} {\n"
"if {${.domain} eq \"\"} {\n"
"set .domain [::xotcl::self callingobject]}\n"
"if {${.domain} ne \"\"} {\n"
"${.domain} __invalidateobjectparameter\n"
"::xotcl::dispatch ${.domain} ::xotcl::cmd::Class::forward \\\n"
"{*}[expr {${.per-object} ? \"-per-object\" : \"\"}] ${.name} \\\n"
"${.manager} [list %1 [${.manager} defaultmethods]] %self \\\n"
"\"%-per-object [info exists .forward-per-object]\" \\\n"
"%proc}}\n"
"::xotcl::MetaSlot create ::xotcl::InfoSlot\n"
"createBootstrapAttributeSlots ::xotcl::InfoSlot {\n"
"{multivalued true}\n"
"{elementtype ::xotcl2::Class}}\n"
"::xotcl::relation ::xotcl::InfoSlot superclass ::xotcl::Slot\n"
"::xotcl::InfoSlot method -public get {obj prop} {\n"
"$obj info $prop}\n"
"::xotcl::InfoSlot method -public add {obj prop value {pos 0}} {\n"
"if {![set .multivalued]} {\n"
"error \"Property $prop of ${.domain}->$obj ist not multivalued\"}\n"
"puts stderr \"adding infoslot: $obj $prop [linsert [$obj info $prop] $pos $value]\"\n"
"$obj $prop [linsert [$obj info $prop] $pos $value]}\n"
"::xotcl::InfoSlot method -public delete {-nocomplain:switch obj prop value} {\n"
"puts stderr infoslot-delete-[self args]\n"
"set old [$obj info $prop]\n"
"if {[string first * $value] > -1 || [string first \\[ $value] > -1} {\n"
"if {${.elementtype} ne \"\" && ![string match ::* $value]} {\n"
"set value ::$value}\n"
"return [$obj $prop [lsearch -all -not -glob -inline $old $value]]} elseif {${.elementtype} ne \"\"} {\n"
"if {[string first :: $value] == -1} {\n"
"if {![::xotcl::is $value object]} {\n"
"error \"$value does not appear to be an object\"}\n"
"set value [::xotcl::dispatch $value -objscope ::xotcl::self]}\n"
"if {![::xotcl::is ${.elementtype} class]} {\n"
"error \"$value does not appear to be of type ${.elementtype}\"}}\n"
"set p [lsearch -exact $old $value]\n"
"if {$p > -1} {\n"
"$obj $prop [lreplace $old $p $p]} else {\n"
"error \"$value is not a $prop of $obj (valid are: $old)\"}}\n"
"::xotcl::MetaSlot alloc ::xotcl::InterceptorSlot\n"
"::xotcl::relation ::xotcl::InterceptorSlot superclass ::xotcl::InfoSlot\n"
"::xotcl::alias ::xotcl::InterceptorSlot set ::xotcl::relation ;# for backwards compatibility\n"
"::xotcl::alias ::xotcl::InterceptorSlot assign ::xotcl::relation\n"
"::xotcl::InterceptorSlot method -public get {obj -per-object:switch prop} {\n"
"::xotcl::relation $obj {*}[expr {${per-object} ? \"-per-object\" : \"\"}] $prop}\n"
"::xotcl::InterceptorSlot method -public add {obj -per-object:switch prop value {pos 0}} {\n"
"if {![set .multivalued]} {\n"
"error \"Property $prop of ${.domain}->$obj ist not multivalued\"}\n"
"set perObject [expr {${per-object} ? \"-per-object\" : \"\"}]\n"
"set oldSetting [::xotcl::relation $obj {*}$perObject $prop]\n"
"::xotcl::relation $obj {*}$perObject $prop [linsert $oldSetting $pos $value]}\n"
"proc ::xotcl::register_system_slots {os} {\n"
"${os}::Object alloc ${os}::Class::slot\n"
"${os}::Object alloc ${os}::Object::slot\n"
"::xotcl::InfoSlot create ${os}::Class::slot::superclass -type relation\n"
"::xotcl::alias           ${os}::Class::slot::superclass assign ::xotcl::relation\n"
"::xotcl::InfoSlot create ${os}::Object::slot::class -type relation\n"
"::xotcl::alias           ${os}::Object::slot::class assign ::xotcl::relation\n"
"::xotcl::InterceptorSlot create ${os}::Object::slot::mixin \\\n"
"-type relation\n"
"::xotcl::InterceptorSlot create ${os}::Object::slot::filter \\\n"
"-elementtype \"\" -type relation}\n"
"::xotcl::register_system_slots ::xotcl2\n"
"::xotcl::MetaSlot __invalidateobjectparameter\n"
"::xotcl::MetaSlot create ::xotcl::Attribute -superclass ::xotcl::Slot\n"
"createBootstrapAttributeSlots ::xotcl::Attribute {\n"
"{value_check once}\n"
"initcmd\n"
"valuecmd\n"
"valuechangedcmd}\n"
"::xotcl::Attribute method __default_from_cmd {obj cmd var sub op} {\n"
"$obj trace remove variable $var $op [list [::xotcl::self] [::xotcl::self proc] $obj $cmd]\n"
"::xotcl::setinstvar $obj $var [$obj eval $cmd]}\n"
"::xotcl::Attribute method __value_from_cmd {obj cmd var sub op} {\n"
"::xotcl::setinstvar $obj $var [$obj eval $cmd]}\n"
"::xotcl::Attribute method __value_changed_cmd {obj cmd var sub op} {\n"
"eval $cmd}\n"
"::xotcl::Attribute method check_single_value { {-keep_old_value:boolean true} value predicate type obj var} {\n"
"if {![expr $predicate]} {\n"
"if {[$obj exists __oldvalue($var)]} {\n"
"::xotcl::setinstvar $obj $var [::xotcl::setinstvar $obj __oldvalue($var)]} else {\n"
"$obj unset -nocomplain $var}\n"
"error \"'$value' is not of type $type\"}\n"
"if {$keep_old_value} {::xotcl::setinstvar $obj __oldvalue($var) $value}}\n"
"::xotcl::Attribute method check_multiple_values {values predicate type obj var} {\n"
"foreach value $values {\n"
".check_single_value -keep_old_value false $value $predicate $type $obj $var}\n"
"::xotcl::setinstvar $obj __oldvalue($var) $value}\n"
"::xotcl::Attribute method mk_type_checker {} {\n"
"set __initcmd \"\"\n"
"if {[.exists type]} {\n"
"if {[::xotcl::is ${.type} class]} {\n"
"set predicate [subst -nocommands {\n"
"[::xotcl::is \\$value object] && [::xotcl::is \\$value type ${.type}]}]} elseif {[llength ${.type}]>1} {\n"
"set predicate \"\\[${.type} \\$value\\]\"} else {\n"
"set predicate \"\\[.type=${.type} ${.name} \\$value\\]\"}\n"
"append .valuechangedcmd [subst {\n"
"[expr {${.multivalued} ? \".check_multiple_values\" : \".check_single_value\"}] \\[::xotcl::setinstvar \\$obj ${.name}\\] \\\n"
"{$predicate} [list ${.type}] \\$obj ${.name}}]\n"
"append __initcmd [subst -nocommands {\n"
"if {[.exists ${.name}]} {set .__oldvalue(${.name}) [set .${.name}]}\\n}]}\n"
"return $__initcmd}\n"
"::xotcl::Attribute method init {} {\n"
"next ;# do first ordinary slot initialization\n"
"set __initcmd \"\"\n"
"if {[.exists default]} {} elseif [.exists initcmd] {\n"
"append __initcmd \".trace add variable [list ${.name}] read \\\n"
"\\[list [::xotcl::self] __default_from_cmd \\[::xotcl::self\\] [list [set .initcmd]]\\]\\n\"} elseif [.exists valuecmd] {\n"
"append __initcmd \".trace add variable [list ${.name}] read \\\n"
"\\[list [::xotcl::self] __value_from_cmd \\[::xotcl::self\\] [list [set .valuecmd]]\\]\"}\n"
"if {[.exists valuechangedcmd]} {\n"
"append __initcmd \".trace add variable [list ${.name}] write \\\n"
"\\[list [::xotcl::self] __value_changed_cmd \\[::xotcl::self\\] [list [set .valuechangedcmd]]\\]\"}\n"
"if {$__initcmd ne \"\"} {\n"
"set .initcmd $__initcmd}}\n"
"::xotcl2::Class create ::xotcl::Slot::Nocheck {\n"
".method check_single_value args {;}\n"
".method check_multiple_values args {;}\n"
".method mk_type_checker args {return \"\"}}\n"
"::xotcl2::Class create ::xotcl::Slot::Optimizer {\n"
".method method args  {::xotcl::next; .optimize}\n"
".method forward args {::xotcl::next; .optimize}\n"
".method init args    {::xotcl::next; .optimize}\n"
".method -public optimize {} {\n"
"if {[set .multivalued]} return\n"
"if {[set .defaultmethods] ne {get assign}} return\n"
"if {[.info callable -which assign] ne \"::xotcl::Slot alias assign ::xotcl::setinstvar\"} return\n"
"if {[.info callable -which get]    ne \"::xotcl::Slot alias get ::xotcl::setinstvar\"} return\n"
"::xotcl::dispatch ${.domain} ::xotcl::cmd::Class::setter {*}[expr {${.per-object} ? \"-per-object\" : \"\"}] ${.name}}}\n"
"::xotcl::Attribute mixin add ::xotcl::Slot::Optimizer\n"
"::xotcl2::Class create ::xotcl::ScopedNew -superclass ::xotcl2::Class\n"
"createBootstrapAttributeSlots ::xotcl::ScopedNew {\n"
"{withclass ::xotcl2::Object}\n"
"inobject}\n"
"::xotcl::ScopedNew method init {} {\n"
".method -public new {-childof args} {\n"
"::xotcl::instvar -object [::xotcl::self class] {inobject object} withclass\n"
"if {![::xotcl::is $object object]} {\n"
"$withclass create $object}\n"
"eval ::xotcl::next -childof $object $args}}\n"
"::xotcl2::Object method -public contains {\n"
"{-withnew:boolean true}\n"
"-object\n"
"{-class ::xotcl2::Object}\n"
"cmds} {\n"
"if {![info exists object]} {set object [::xotcl::self]}\n"
"if {![::xotcl::is $object object]} {$class create $object}\n"
"$object requireNamespace\n"
"if {$withnew} {\n"
"set m [::xotcl::ScopedNew new \\\n"
"-inobject $object -withclass $class -volatile]\n"
"::xotcl2::Class mixin add $m end\n"
"namespace eval $object $cmds\n"
"::xotcl2::Class mixin delete $m} else {\n"
"namespace eval $object $cmds}}\n"
"::xotcl2::Class forward slots %self contains \\\n"
"-object {%::xotcl::dispatch [::xotcl::self] -objscope ::subst [::xotcl::self]::slot}\n"
"::xotcl2::Class method -public parameter arglist {\n"
"if {![::xotcl::is [::xotcl::self]::slot object]} {\n"
"::xotcl2::Object create [::xotcl::self]::slot}\n"
"foreach arg $arglist {\n"
"set l [llength $arg]\n"
"set name [lindex $arg 0]\n"
"if {[string first : $name] > -1} {\n"
"foreach {name type} [split $name :] break\n"
"if {$type eq \"required\"} {\n"
"set required 1\n"
"unset type}}\n"
"set cmd [list ::xotcl::Attribute create [::xotcl::self]::slot::$name]\n"
"if {[info exists type]} {\n"
"lappend cmd -type $type\n"
"unset type}\n"
"if {[info exists required]} {\n"
"lappend cmd -required 1\n"
"unset required}\n"
"if {$l == 1} {\n"
"eval $cmd} elseif {$l == 2} {\n"
"lappend cmd -default [lindex $arg 1]\n"
"eval $cmd} elseif {$l == 3 && [lindex $arg 1] eq \"-default\"} {\n"
"lappend cmd -default [lindex $arg 2]\n"
"eval $cmd} else {\n"
"set paramstring [string range $arg [expr {[string length $name]+1}] end]\n"
"if {[string match {[$\\[]*} $paramstring]} {\n"
"lappend cmd -default $paramstring\n"
"eval $cmd\n"
"continue}\n"
"set po ::xotcl2::Class::Parameter\n"
"puts stderr \"deprecated parameter usage '$arg'; use '-slots {Attribute ...}' instead\"\n"
"set cl [::xotcl::self]\n"
"::xotcl::setinstvar $po name $name\n"
"::xotcl::setinstvar $po cl [::xotcl::self]\n"
"::eval $po configure [lrange $arg 1 end]\n"
"if {[$po exists extra] || [$po exists setter] ||\n"
"[$po exists getter] || [$po exists access]} {\n"
"::xotcl::instvar -object $po extra setter getter access defaultParam\n"
"if {![info exists extra]} {set extra \"\"}\n"
"if {![info exists defaultParam]} {set defaultParam \"\"}\n"
"if {![info exists setter]} {set setter set}\n"
"if {![info exists getter]} {set getter set}\n"
"if {![info exists access]} {set access ::xotcl::my}\n"
"$cl method -public $name args \"\n"
"if {\\[llength \\$args] == 0} {\n"
"return \\[$access $getter $extra $name\\]} else {\n"
"return \\[eval $access $setter $extra $name \\$args $defaultParam \\]}\"\n"
"foreach instvar {extra defaultParam setter getter access} {\n"
"$po unset -nocomplain $instvar}} else {\n"
".setter $name}}}\n"
"::xotcl::setinstvar [::xotcl::self]::slot __parameter $arglist}\n"
"::xotcl2::Class create ::xotcl::CopyHandler -parameter {\n"
"{targetList \"\"}\n"
"{dest \"\"}\n"
"objLength} {\n"
".method makeTargetList {t} {\n"
"lappend .targetList $t\n"
"if {[::xotcl::is $t object]} {\n"
"if {[$t info hasnamespace]} {\n"
"set children [$t info children]} else {\n"
"return}}\n"
"foreach c [namespace children $t] {\n"
"if {![::xotcl::is $c object]} {\n"
"lappend children [namespace children $t]}}\n"
"foreach c $children {\n"
".makeTargetList $c}}\n"
".method copyNSVarsAndCmds {orig dest} {\n"
"::xotcl::namespace_copyvars $orig $dest\n"
"::xotcl::namespace_copycmds $orig $dest}\n"
".method getDest origin {\n"
"set tail [string range $origin [set .objLength] end]\n"
"return ::[string trimleft [set .dest]$tail :]}\n"
".method copyTargets {} {\n"
"foreach origin [set .targetList] {\n"
"set dest [.getDest $origin]\n"
"if {[::xotcl::is $origin object]} {\n"
"if {[::xotcl::is $origin class]} {\n"
"set cl [[$origin info class] create $dest -noinit]\n"
"set obj $cl\n"
"$cl superclass [$origin info superclass]\n"
"$cl instinvar  [$origin info instinvar]\n"
"$cl instfilter [$origin info instfilter -guards]\n"
"$cl instmixin  [$origin info instmixin]\n"
".copyNSVarsAndCmds ::xotcl::classes$origin ::xotcl::classes$dest} else {\n"
"set obj [[$origin info class] create $dest -noinit]}\n"
"$obj invar  [$origin info invar]\n"
"$obj check  [$origin info check]\n"
"$obj mixin  [$origin info mixin]\n"
"$obj filter [$origin info filter -guards]\n"
"if {[$origin info hasnamespace]} {\n"
"$obj requireNamespace}} else {\n"
"namespace eval $dest {}}\n"
".copyNSVarsAndCmds $origin $dest\n"
"foreach i [$origin info forward] {\n"
"eval [concat $dest forward $i [$origin info forward -definition $i]]}\n"
"if {[::xotcl::is $origin class]} {\n"
"foreach i [$origin info instforward] {\n"
"eval [concat $dest instforward $i [$origin info instforward -definition $i]]}}\n"
"set traces [list]\n"
"foreach var [$origin info vars] {\n"
"set cmds [::xotcl::dispatch $origin -objscope ::trace info variable $var]\n"
"if {$cmds ne \"\"} {\n"
"foreach cmd $cmds {\n"
"foreach {op def} $cmd break\n"
"if {[lindex $def 0] eq $origin} {\n"
"set def [concat $dest [lrange $def 1 end]]}\n"
"$dest trace add variable $var $op $def}}}}\n"
"foreach origin [set .targetList] {\n"
"if {[::xotcl::is $origin class]} {\n"
"set dest [.getDest $origin]\n"
"foreach oldslot [$origin info slots] {\n"
"set newslot ${dest}::slot::[namespace tail $oldslot]\n"
"if {[$oldslot domain] eq $origin}   {$newslot domain $cl}\n"
"if {[$oldslot manager] eq $oldslot} {$newslot manager $newslot}}}}}\n"
".method -public copy {obj dest} {\n"
"set .objLength [string length $obj]\n"
"set .dest $dest\n"
".makeTargetList $obj\n"
".copyTargets}}\n"
"::xotcl2::Object method -public copy newName {\n"
"if {[string compare [string trimleft $newName :] [string trimleft [::xotcl::self] :]]} {\n"
"[::xotcl::CopyHandler new -volatile] copy [::xotcl::self] $newName}}\n"
"::xotcl2::Object method -public move newName {\n"
"if {[string trimleft $newName :] ne [string trimleft [::xotcl::self] :]} {\n"
"if {$newName ne \"\"} {\n"
".copy $newName}\n"
"if {[::xotcl::is [::xotcl::self] class] && $newName ne \"\"} {\n"
"foreach subclass [.info subclass] {\n"
"set scl [$subclass info superclass]\n"
"if {[set index [lsearch -exact $scl [::xotcl::self]]] != -1} {\n"
"set scl [lreplace $scl $index $index $newName]\n"
"$subclass superclass $scl}}	}\n"
".destroy}}\n"
"::xotcl2::Object create ::xotcl::@ {\n"
".method unknown args {}}\n"
"namespace eval ::xotcl {\n"
"namespace export @ Attribute\n"
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
"puts stderr \"current=[namespace current], ul=[uplevel {namespace current}]\"\n"
"if {$callingNs ne \"::xotcl\"} {uplevel {namespace import -force ::xotcl::*}}}\n"
"default {\n"
"if {$callingNs ne \"::xotcl\"} {uplevel {namespace import -force ::xotcl::*}}\n"
"if {$callingNs ne \"::xotcl2\"} {uplevel {namespace import -force ::xotcl2::*}}}}}\n"
"unset bootstrap}\n"
"";

