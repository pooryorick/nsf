#!/usr/bin/env tclsh
#
# A small script file that creates a static array from a Tcl-
# script for inclusion in c programs
#
#   Copyright (C) 2010-2014 Gustaf Neumann
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set f [open [lindex $argv 0]]
set content [read $f]
close $f

regsub -all {\\} $content && content
regsub -all {"} $content {\"} content             ;#"
regsub -all "\[ \]+\n" $content \n content        ;# remove trailing space
regsub -all "\n\[ \t\]+" $content \n content      ;# remove leading space
while {[regsub -all "\n#\[^\n\]*\n" $content \n content]>0} {
    ;# remove comment lines
}
regsub -all "\n#\[^\n\]*\n" $content \n content   ;# remove comment lines
regsub -all "\[\n\]+" $content \n content         ;# remove empty lines
regsub -all "\n}" $content "}" content            ;# newlines btwn braces
regsub -all "\n" $content "\\n\"\n\"" content

puts "/* Generated by mk_predefined.tcl */"
puts "static char cmd\[\] = "
puts "\"$content\";"
puts ""


