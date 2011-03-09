static char cmd[] = 
"namespace eval ::nsf {\n"
"namespace export next current self\n"
"namespace eval ::nsf::method::create {\n"
"namespace export alias}\n"
"namespace export configure finalize interp is my relation\n"
"proc ::nsf::method::provide {require_name definition {script \"\"}} {\n"
"set ::nsf::methodIndex($require_name) [list definition $definition script $script]}\n"
"proc ::nsf::method::require {object name {per_object 0}} {\n"
"set key ::nsf::methodIndex($name)\n"
"if {[info exists $key]} {\n"
"array set \"\" [set $key]\n"
"if {$(script) ne \"\"} {\n"
"eval $(script)}\n"
"if {$per_object} {\n"
"set cmd [linsert $(definition) 1 -per-object]\n"
"return [eval [linsert $cmd 1 $object]]} else {\n"
"return [eval [linsert $(definition) 1 $object]]}} else {\n"
"error \"cannot require method $name for $object, method unknown\"}}\n"
"nsf::proc ::nsf::method::delete {object:object -per-object:switch methodName} {\n"
"set scope [expr {${per-object} ? \"object\" : \"class\"}]\n"
"if {[$object ::nsf::methods::${scope}::info::method exists $methodName]} {\n"
"::nsf::method::create $object {*}[expr {${per-object} ? \"-per-object\" : \"\"}] $methodName \"\" \"\"} else {\n"
"error \"Object $object: method $methodName is not defined\"}}\n"
"::proc strip_proc_name {name} {\n"
"if {[string match ::nsf::procs::* $name]} {\n"
"return [string range $name 12 end]} elseif {[string match nsf::procs::* $name]} {\n"
"return [string range $name 12 end]} else {\n"
"return $name}}\n"
"::nsf::proc ::nsf::mixin {object -per-object:switch classes} {\n"
"set rel [expr {${per-object} ? \"object-mixin\" : \"class-mixin\"}]\n"
"if {[lindex $classes 0] ne \"\"} {\n"
"set oldSetting [::nsf::relation $object $rel]\n"
"uplevel [list ::nsf::relation $object $rel [linsert $oldSetting 0 $classes]]} else {\n"
"uplevel [list ::nsf::relation $object $rel \"\"]}}\n"
"::nsf::method::provide autoname {::nsf::method::alias autoname ::nsf::methods::object::autoname}\n"
"::nsf::method::provide exists   {::nsf::method::alias exists   ::nsf::methods::object::exists}\n"
"proc ::nsf::exithandler {args} {\n"
"lassign $args op value\n"
"switch $op {\n"
"set {::proc ::nsf::__exithandler {} $value}\n"
"get {::info body ::nsf::__exithandler}\n"
"unset {proc ::nsf::__exithandler args {;}}\n"
"default {error \"syntax: ::nsf::exithandler $::nsf::parametersyntax(::nsf::exithandler)\"}}}\n"
"::nsf::exithandler unset\n"
"if {[info command ::ns_log] ne \"\"} {\n"
"proc ::nsf::log {level msg} {\n"
"ns_log $level \"nsf: $msg\"}} else {\n"
"proc ::nsf::log {level msg} {\n"
"puts stderr \"$level: $msg\"}}\n"
"proc ::nsf::deprecated {what oldCmd newCmd} {\n"
"set msg \"**\\n** The $what $oldcmd is deprecated.\"\n"
"if {$newCmd ne \"\"} {append msg \" use $newCmd instead.\"}\n"
"append msg \"\\n**\\n\"\n"
"nsf::log Warning $msg}\n"
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
"namespace export tmpdir\n"
"if {![info exists ::env(HOME)]} {set ::env(HOME) /root}\n"
"set ::nsf::parametersyntax(::nsf::xotclnext) \"?--noArgs? ?arg ...?\"\n"
"set ::nsf::parametersyntax(::nsf::__unset_unknown_args) \"\"\n"
"set ::nsf::parametersyntax(::nsf::exithandler) \"?get?|?set cmds?|?unset?\"}\n"
"";

