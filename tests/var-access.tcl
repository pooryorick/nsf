package require nx
package require nx::test

namespace eval ::nx::var1 {
  namespace ensemble create -map {
    exists ::nsf::existsvar 
    import ::nsf::importvar 
    set ::nsf::setvar
  }
}

::nx::Object create ::nx::var2 {
  :alias exists ::nsf::existsvar 
  :alias import ::nsf::importvar
  :alias set ::nsf::setvar
}

Test parameter count 10000
Test case dummy {
  nx::Object create o {
    set :x 1
  }
  nx::Object create p {
    set :y 1
    :method foo0 {} {
      incr :y
    }
    :method foo1 {} {
      o eval {incr :x}
    }
    :method foo2 {} {
      ::nsf::importvar o x
      incr x
    }
    :method foo3 {} {
      ::nx::var1 import o x
      incr x
    }
    :method foo4 {} {
      ::nx::var2 import o x
      incr x
    }
  }
  
  ? {::nsf::setvar o x} 1
  ? {::nsf::existsvar o x} 1
  ? {::nsf::existsvar o y} 0

  ? {::nx::var1 set o x} 1
  ? {::nx::var1 exists o x} 1
  ? {::nx::var1 exists o y} 0

  ? {::nx::var2 set o x} 1
  ? {::nx::var2 exists o x} 1
  ? {::nx::var2 exists o y} 0

  ? {p foo0} 2

  ? {p foo1} 2
  ? {::nsf::setvar o x} 10002

  ? {p foo2} 10003
  ? {::nsf::setvar o x} 20003

  ? {p foo3} 20004
  ? {::nsf::setvar o x} 30004

  ? {p foo4} 30005
  ? {::nsf::setvar o x} 40005
}

puts stderr =====END
