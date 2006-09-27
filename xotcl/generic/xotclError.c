/* -*- Mode: c++ -*-
 * $Id: xotclError.c,v 1.5 2006/09/27 08:12:40 neumann Exp $
 *  
 *  Extended Object Tcl (XOTcl)
 *
 *  Copyright (C) 1999-2006 Gustaf Neumann, Uwe Zdun
 *
 *
 *  xotclError.c --
 *  
 *  error return functions for XOTcl
 *  
 */

#include "xotclInt.h"

int
XOTclErrMsg(Tcl_Interp *in, char *msg, Tcl_FreeProc* type) {
    Tcl_SetResult(in, msg, type);
    return TCL_ERROR;
}

int
XOTclVarErrMsg TCL_VARARGS_DEF (Tcl_Interp *, arg1)
{
    va_list argList;
    char *string;
    Tcl_Interp *in;

    in = TCL_VARARGS_START(Tcl_Interp *, arg1, argList);
    Tcl_ResetResult(in);
    while (1) {
      string = va_arg(argList, char *);
      if (string == NULL) {
        break;
      }
      Tcl_AppendResult(in, string, (char *) NULL);
    }
    va_end(argList);
    return TCL_ERROR;
}


int
XOTclErrInProc (Tcl_Interp *in, Tcl_Obj *objName,
		Tcl_Obj *clName, char *procName) {
    Tcl_DString errMsg;
    char *cName, *space;
    ALLOC_DSTRING(&errMsg, "\n    ");
    if (clName) {
      cName = ObjStr(clName);
      space = " ";
    } else {
      cName = "";
      space ="";
    }
    Tcl_DStringAppend(&errMsg, ObjStr(objName),-1);
    Tcl_DStringAppend(&errMsg, space, -1);
    Tcl_DStringAppend(&errMsg, cName, -1);
    Tcl_DStringAppend(&errMsg, "->", 2);
    Tcl_DStringAppend(&errMsg, procName, -1);
    Tcl_AddErrorInfo (in, Tcl_DStringValue(&errMsg));
    DSTRING_FREE(&errMsg);
    return TCL_ERROR;
}

int
XOTclObjErrArgCnt(Tcl_Interp *in, Tcl_Obj *cmdname, char *arglist) {
  Tcl_ResetResult(in);
  Tcl_AppendResult(in, "wrong # args: should be {", (char *) NULL);
  if (cmdname) {
    Tcl_AppendResult(in, ObjStr(cmdname), " ", (char *) NULL);
  }
  if (arglist != 0) Tcl_AppendResult(in, arglist, (char *) NULL);
  Tcl_AppendResult(in, "}", (char *) NULL);
  return TCL_ERROR;
}

int
XOTclErrBadVal(Tcl_Interp *in, char *context, char *expected, char *value) {
  Tcl_ResetResult(in);
  Tcl_AppendResult(in, context, ": expected ", expected, " but got '", 
		   value, "'", (char *) NULL);
  return TCL_ERROR;
}

int
XOTclErrBadVal_(Tcl_Interp *in, char *expected, char *value) {
  fprintf(stderr, "Deprecated call, recompile your program with xotcl 1.5 or newer\n");
  Tcl_ResetResult(in);
  Tcl_AppendResult(in, ": expected ", expected, " but got '", 
		   value, "'", (char *) NULL);
  return TCL_ERROR;
}

extern int
XOTclObjErrType(Tcl_Interp *in, Tcl_Obj *nm, char *wt) {
  Tcl_ResetResult(in);
  Tcl_AppendResult(in,"'",ObjStr(nm), "' method should be called on '",
		   wt, "'", (char *) NULL);
  return TCL_ERROR;
}
