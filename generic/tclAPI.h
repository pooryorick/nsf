
typedef struct {
  char *methodName;
  Tcl_ObjCmdProc *proc;
  CONST interfaceDefinition ifd;
} methodDefinition;

static int parseObjv(Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[],
		     int idx, parseContext *pc);

static int getMatchObject(Tcl_Interp *interp, Tcl_Obj *patternObj, Tcl_Obj *origObj,
			  XOTclObject **matchObject, char **pattern);
  
char *method_command_namespace_names[] = {
  "::xotcl::cmd::ObjectInfo",
  "::xotcl::cmd::Object",
  "::xotcl::cmd::ClassInfo",
  "::xotcl::cmd::NonposArgs",
  "::xotcl::cmd::Class"
};
static int XOTclCheckBooleanArgsStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCheckRequiredArgsStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCAllocMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCCreateMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCDeallocMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCInstFilterGuardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCInstForwardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCInstMixinGuardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCInstParametercmdMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCInstProcMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCInstProcMethodCStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCInvariantsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCNewMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCRecreateMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclCUnknownMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoHeritageMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstancesMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstargsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstbodyMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstcommandsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstdefaultMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstfilterMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstfilterguardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstforwardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstinvarMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstmixinMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstmixinguardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstmixinofMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstnonposargsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstparametercmdMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstpostMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstpreMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoInstprocsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoMixinofMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoParameterMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoSlotsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoSubclassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclClassInfoSuperclassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoArgsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoBodyMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoCheckMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoChildrenMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoClassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoCommandsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoDefaultMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoFilterMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoFilterguardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoForwardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoHasnamespaceMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoInvarMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoMethodsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoMixinMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoMixinguardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoNonposargsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoParametercmdMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoParentMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoPostMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoPreMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoPrecedenceMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoProcsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoSlotObjectsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclObjInfoVarsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOAutonameMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOCheckMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOCleanupMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOConfigureMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclODestroyMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOExistsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOFilterGuardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOFilterSearchMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOForwardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOInstVarMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOInvariantsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOIsClassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOIsMetaClassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOIsMixinMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOIsObjectMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOIsTypeMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOMixinGuardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclONextMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclONoinitMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOParametercmdMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOProcMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOProcSearchMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclORequireNamespaceMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOSetMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOSetvaluesMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOUplevelMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOUpvarMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOVolatileMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclOVwaitMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);
static int XOTclAliasCmdStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv []);

static int XOTclCheckBooleanArgs(Tcl_Interp *interp, char *name, Tcl_Obj *value);
static int XOTclCheckRequiredArgs(Tcl_Interp *interp, char *name, Tcl_Obj *value);
static int XOTclCAllocMethod(Tcl_Interp *interp, XOTclClass *cl, char *name);
static int XOTclCCreateMethod(Tcl_Interp *interp, XOTclClass *cl, char *name, int objc, Tcl_Obj *CONST objv[]);
static int XOTclCDeallocMethod(Tcl_Interp *interp, XOTclClass *cl, Tcl_Obj *object);
static int XOTclCInstFilterGuardMethod(Tcl_Interp *interp, XOTclClass *cl, char *filter, Tcl_Obj *guard);
static int XOTclCInstForwardMethod(Tcl_Interp *interp, XOTclClass *cl, Tcl_Obj *method, Tcl_Obj *withDefault, int withEarlybinding, Tcl_Obj *withMethodprefix, int withObjscope, Tcl_Obj *withOnerror, int withVerbose, Tcl_Obj *target, int nobjc, Tcl_Obj *CONST nobjv[]);
static int XOTclCInstMixinGuardMethod(Tcl_Interp *interp, XOTclClass *cl, char *mixin, Tcl_Obj *guard);
static int XOTclCInstParametercmdMethod(Tcl_Interp *interp, XOTclClass *cl, char *name);
static int XOTclCInstProcMethod(Tcl_Interp *interp, XOTclClass *cl, Tcl_Obj *name, Tcl_Obj *args, Tcl_Obj *body, Tcl_Obj *precondition, Tcl_Obj *postcondition);
static int XOTclCInstProcMethodC(Tcl_Interp *interp, XOTclClass *cl, Tcl_Obj *name, Tcl_Obj *args, Tcl_Obj *body, Tcl_Obj *precondition, Tcl_Obj *postcondition);
static int XOTclCInvariantsMethod(Tcl_Interp *interp, XOTclClass *cl, Tcl_Obj *invariantlist);
static int XOTclCNewMethod(Tcl_Interp *interp, XOTclClass *cl, XOTclObject *withChildof, int nobjc, Tcl_Obj *CONST nobjv[]);
static int XOTclCRecreateMethod(Tcl_Interp *interp, XOTclClass *cl, Tcl_Obj *name, int objc, Tcl_Obj *CONST objv[]);
static int XOTclCUnknownMethod(Tcl_Interp *interp, XOTclClass *cl, char *name, int objc, Tcl_Obj *CONST objv[]);
static int XOTclClassInfoHeritageMethod(Tcl_Interp *interp, XOTclClass *class, char *pattern);
static int XOTclClassInfoInstancesMethod(Tcl_Interp *interp, XOTclClass *class, int withClosure, char *patternString, XOTclObject *patternObj);
static int XOTclClassInfoInstargsMethod(Tcl_Interp *interp, XOTclClass *class, char *methodName);
static int XOTclClassInfoInstbodyMethod(Tcl_Interp *interp, XOTclClass *class, char *methodName);
static int XOTclClassInfoInstcommandsMethod(Tcl_Interp *interp, XOTclClass *class, char *pattern);
static int XOTclClassInfoInstdefaultMethod(Tcl_Interp *interp, XOTclClass *class, char *methodName, char *arg, Tcl_Obj *var);
static int XOTclClassInfoInstfilterMethod(Tcl_Interp *interp, XOTclClass *class, int withGuards, char *pattern);
static int XOTclClassInfoInstfilterguardMethod(Tcl_Interp *interp, XOTclClass *class, char *filter);
static int XOTclClassInfoInstforwardMethod(Tcl_Interp *interp, XOTclClass *class, int withDefinition, char *pattern);
static int XOTclClassInfoInstinvarMethod(Tcl_Interp *interp, XOTclClass *class);
static int XOTclClassInfoInstmixinMethod(Tcl_Interp *interp, XOTclClass *class, int withClosure, int withGuards, char *patternString, XOTclObject *patternObj);
static int XOTclClassInfoInstmixinguardMethod(Tcl_Interp *interp, XOTclClass *class, char *mixin);
static int XOTclClassInfoInstmixinofMethod(Tcl_Interp *interp, XOTclClass *class, int withClosure, char *patternString, XOTclObject *patternObj);
static int XOTclClassInfoInstnonposargsMethod(Tcl_Interp *interp, XOTclClass *class, char *methodName);
static int XOTclClassInfoInstparametercmdMethod(Tcl_Interp *interp, XOTclClass *class, char *pattern);
static int XOTclClassInfoInstpostMethod(Tcl_Interp *interp, XOTclClass *class, char *methodName);
static int XOTclClassInfoInstpreMethod(Tcl_Interp *interp, XOTclClass *class, char *methodName);
static int XOTclClassInfoInstprocsMethod(Tcl_Interp *interp, XOTclClass *class, char *pattern);
static int XOTclClassInfoMixinofMethod(Tcl_Interp *interp, XOTclClass *class, int withClosure, char *patternString, XOTclObject *patternObj);
static int XOTclClassInfoParameterMethod(Tcl_Interp *interp, XOTclClass *class);
static int XOTclClassInfoSlotsMethod(Tcl_Interp *interp, XOTclClass *class);
static int XOTclClassInfoSubclassMethod(Tcl_Interp *interp, XOTclClass *class, int withClosure, char *patternString, XOTclObject *patternObj);
static int XOTclClassInfoSuperclassMethod(Tcl_Interp *interp, XOTclClass *class, int withClosure, Tcl_Obj *pattern);
static int XOTclObjInfoArgsMethod(Tcl_Interp *interp, XOTclObject *object, char *methodName);
static int XOTclObjInfoBodyMethod(Tcl_Interp *interp, XOTclObject *object, char *methodName);
static int XOTclObjInfoCheckMethod(Tcl_Interp *interp, XOTclObject *object);
static int XOTclObjInfoChildrenMethod(Tcl_Interp *interp, XOTclObject *object, char *pattern);
static int XOTclObjInfoClassMethod(Tcl_Interp *interp, XOTclObject *object);
static int XOTclObjInfoCommandsMethod(Tcl_Interp *interp, XOTclObject *object, char *pattern);
static int XOTclObjInfoDefaultMethod(Tcl_Interp *interp, XOTclObject *object, char *methodName, char *arg, Tcl_Obj *var);
static int XOTclObjInfoFilterMethod(Tcl_Interp *interp, XOTclObject *object, int withOrder, int withGuards, char *pattern);
static int XOTclObjInfoFilterguardMethod(Tcl_Interp *interp, XOTclObject *object, char *filter);
static int XOTclObjInfoForwardMethod(Tcl_Interp *interp, XOTclObject *object, int withDefinition, char *pattern);
static int XOTclObjInfoHasnamespaceMethod(Tcl_Interp *interp, XOTclObject *object);
static int XOTclObjInfoInvarMethod(Tcl_Interp *interp, XOTclObject *object);
static int XOTclObjInfoMethodsMethod(Tcl_Interp *interp, XOTclObject *object, int withNoprocs, int withNocmds, int withNomixins, int withIncontext, char *pattern);
static int XOTclObjInfoMixinMethod(Tcl_Interp *interp, XOTclObject *object, int withGuards, int withOrder, char *patternString, XOTclObject *patternObj);
static int XOTclObjInfoMixinguardMethod(Tcl_Interp *interp, XOTclObject *object, char *mixin);
static int XOTclObjInfoNonposargsMethod(Tcl_Interp *interp, XOTclObject *object, char *methodName);
static int XOTclObjInfoParametercmdMethod(Tcl_Interp *interp, XOTclObject *object, char *pattern);
static int XOTclObjInfoParentMethod(Tcl_Interp *interp, XOTclObject *object);
static int XOTclObjInfoPostMethod(Tcl_Interp *interp, XOTclObject *object, char *methodName);
static int XOTclObjInfoPreMethod(Tcl_Interp *interp, XOTclObject *object, char *methodName);
static int XOTclObjInfoPrecedenceMethod(Tcl_Interp *interp, XOTclObject *object, int withIntrinsic, char *pattern);
static int XOTclObjInfoProcsMethod(Tcl_Interp *interp, XOTclObject *object, char *pattern);
static int XOTclObjInfoSlotObjectsMethod(Tcl_Interp *interp, XOTclObject *object, char *pattern);
static int XOTclObjInfoVarsMethod(Tcl_Interp *interp, XOTclObject *object, char *pattern);
static int XOTclOAutonameMethod(Tcl_Interp *interp, XOTclObject *obj, int withInstance, int withReset, Tcl_Obj *name);
static int XOTclOCheckMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *flag);
static int XOTclOCleanupMethod(Tcl_Interp *interp, XOTclObject *obj);
static int XOTclOConfigureMethod(Tcl_Interp *interp, XOTclObject *obj, int objc, Tcl_Obj *CONST objv[]);
static int XOTclODestroyMethod(Tcl_Interp *interp, XOTclObject *obj);
static int XOTclOExistsMethod(Tcl_Interp *interp, XOTclObject *obj, char *var);
static int XOTclOFilterGuardMethod(Tcl_Interp *interp, XOTclObject *obj, char *filter, Tcl_Obj *guard);
static int XOTclOFilterSearchMethod(Tcl_Interp *interp, XOTclObject *obj, char *filter);
static int XOTclOForwardMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *method, Tcl_Obj *withDefault, int withEarlybinding, Tcl_Obj *withMethodprefix, int withObjscope, Tcl_Obj *withOnerror, int withVerbose, Tcl_Obj *target, int nobjc, Tcl_Obj *CONST nobjv[]);
static int XOTclOInstVarMethod(Tcl_Interp *interp, XOTclObject *obj, int objc, Tcl_Obj *CONST objv[]);
static int XOTclOInvariantsMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *invariantlist);
static int XOTclOIsClassMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *class);
static int XOTclOIsMetaClassMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *metaclass);
static int XOTclOIsMixinMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *class);
static int XOTclOIsObjectMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *object);
static int XOTclOIsTypeMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *class);
static int XOTclOMixinGuardMethod(Tcl_Interp *interp, XOTclObject *obj, char *mixin, Tcl_Obj *guard);
static int XOTclONextMethod(Tcl_Interp *interp, XOTclObject *obj, int objc, Tcl_Obj *CONST objv[]);
static int XOTclONoinitMethod(Tcl_Interp *interp, XOTclObject *obj);
static int XOTclOParametercmdMethod(Tcl_Interp *interp, XOTclObject *obj, char *name);
static int XOTclOProcMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *name, Tcl_Obj *args, Tcl_Obj *body, Tcl_Obj *precondition, Tcl_Obj *postcondition);
static int XOTclOProcSearchMethod(Tcl_Interp *interp, XOTclObject *obj, char *name);
static int XOTclORequireNamespaceMethod(Tcl_Interp *interp, XOTclObject *obj);
static int XOTclOSetMethod(Tcl_Interp *interp, XOTclObject *obj, Tcl_Obj *var, Tcl_Obj *value);
static int XOTclOSetvaluesMethod(Tcl_Interp *interp, XOTclObject *obj, int objc, Tcl_Obj *CONST objv[]);
static int XOTclOUplevelMethod(Tcl_Interp *interp, XOTclObject *obj, int objc, Tcl_Obj *CONST objv[]);
static int XOTclOUpvarMethod(Tcl_Interp *interp, XOTclObject *obj, int objc, Tcl_Obj *CONST objv[]);
static int XOTclOVolatileMethod(Tcl_Interp *interp, XOTclObject *obj);
static int XOTclOVwaitMethod(Tcl_Interp *interp, XOTclObject *obj, char *varname);
static int XOTclAliasCmd(Tcl_Interp *interp, XOTclObject *object, char *methodName, int withObjscope, int withPer_object, int withProtected, Tcl_Obj *cmdName);

enum {
 XOTclCheckBooleanArgsIdx,
 XOTclCheckRequiredArgsIdx,
 XOTclCAllocMethodIdx,
 XOTclCCreateMethodIdx,
 XOTclCDeallocMethodIdx,
 XOTclCInstFilterGuardMethodIdx,
 XOTclCInstForwardMethodIdx,
 XOTclCInstMixinGuardMethodIdx,
 XOTclCInstParametercmdMethodIdx,
 XOTclCInstProcMethodIdx,
 XOTclCInstProcMethodCIdx,
 XOTclCInvariantsMethodIdx,
 XOTclCNewMethodIdx,
 XOTclCRecreateMethodIdx,
 XOTclCUnknownMethodIdx,
 XOTclClassInfoHeritageMethodIdx,
 XOTclClassInfoInstancesMethodIdx,
 XOTclClassInfoInstargsMethodIdx,
 XOTclClassInfoInstbodyMethodIdx,
 XOTclClassInfoInstcommandsMethodIdx,
 XOTclClassInfoInstdefaultMethodIdx,
 XOTclClassInfoInstfilterMethodIdx,
 XOTclClassInfoInstfilterguardMethodIdx,
 XOTclClassInfoInstforwardMethodIdx,
 XOTclClassInfoInstinvarMethodIdx,
 XOTclClassInfoInstmixinMethodIdx,
 XOTclClassInfoInstmixinguardMethodIdx,
 XOTclClassInfoInstmixinofMethodIdx,
 XOTclClassInfoInstnonposargsMethodIdx,
 XOTclClassInfoInstparametercmdMethodIdx,
 XOTclClassInfoInstpostMethodIdx,
 XOTclClassInfoInstpreMethodIdx,
 XOTclClassInfoInstprocsMethodIdx,
 XOTclClassInfoMixinofMethodIdx,
 XOTclClassInfoParameterMethodIdx,
 XOTclClassInfoSlotsMethodIdx,
 XOTclClassInfoSubclassMethodIdx,
 XOTclClassInfoSuperclassMethodIdx,
 XOTclObjInfoArgsMethodIdx,
 XOTclObjInfoBodyMethodIdx,
 XOTclObjInfoCheckMethodIdx,
 XOTclObjInfoChildrenMethodIdx,
 XOTclObjInfoClassMethodIdx,
 XOTclObjInfoCommandsMethodIdx,
 XOTclObjInfoDefaultMethodIdx,
 XOTclObjInfoFilterMethodIdx,
 XOTclObjInfoFilterguardMethodIdx,
 XOTclObjInfoForwardMethodIdx,
 XOTclObjInfoHasnamespaceMethodIdx,
 XOTclObjInfoInvarMethodIdx,
 XOTclObjInfoMethodsMethodIdx,
 XOTclObjInfoMixinMethodIdx,
 XOTclObjInfoMixinguardMethodIdx,
 XOTclObjInfoNonposargsMethodIdx,
 XOTclObjInfoParametercmdMethodIdx,
 XOTclObjInfoParentMethodIdx,
 XOTclObjInfoPostMethodIdx,
 XOTclObjInfoPreMethodIdx,
 XOTclObjInfoPrecedenceMethodIdx,
 XOTclObjInfoProcsMethodIdx,
 XOTclObjInfoSlotObjectsMethodIdx,
 XOTclObjInfoVarsMethodIdx,
 XOTclOAutonameMethodIdx,
 XOTclOCheckMethodIdx,
 XOTclOCleanupMethodIdx,
 XOTclOConfigureMethodIdx,
 XOTclODestroyMethodIdx,
 XOTclOExistsMethodIdx,
 XOTclOFilterGuardMethodIdx,
 XOTclOFilterSearchMethodIdx,
 XOTclOForwardMethodIdx,
 XOTclOInstVarMethodIdx,
 XOTclOInvariantsMethodIdx,
 XOTclOIsClassMethodIdx,
 XOTclOIsMetaClassMethodIdx,
 XOTclOIsMixinMethodIdx,
 XOTclOIsObjectMethodIdx,
 XOTclOIsTypeMethodIdx,
 XOTclOMixinGuardMethodIdx,
 XOTclONextMethodIdx,
 XOTclONoinitMethodIdx,
 XOTclOParametercmdMethodIdx,
 XOTclOProcMethodIdx,
 XOTclOProcSearchMethodIdx,
 XOTclORequireNamespaceMethodIdx,
 XOTclOSetMethodIdx,
 XOTclOSetvaluesMethodIdx,
 XOTclOUplevelMethodIdx,
 XOTclOUpvarMethodIdx,
 XOTclOVolatileMethodIdx,
 XOTclOVwaitMethodIdx,
 XOTclAliasCmdIdx
} XOTclMethods;


static int
XOTclCheckBooleanArgsStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclCheckBooleanArgsIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *name = (char *)pc.clientData[0];
    Tcl_Obj *value = (Tcl_Obj *)pc.clientData[1];

    return XOTclCheckBooleanArgs(interp, name, value);

  }
}
  
static int
XOTclCheckRequiredArgsStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclCheckRequiredArgsIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *name = (char *)pc.clientData[0];
    Tcl_Obj *value = (Tcl_Obj *)pc.clientData[1];

    return XOTclCheckRequiredArgs(interp, name, value);

  }
}
  
static int
XOTclCAllocMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCAllocMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *name = (char *)pc.clientData[0];

    return XOTclCAllocMethod(interp, cl, name);

  }
}
  
static int
XOTclCCreateMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCCreateMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *name = (char *)pc.clientData[0];

    return XOTclCCreateMethod(interp, cl, name, objc, objv);

  }
}
  
static int
XOTclCDeallocMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCDeallocMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *object = (Tcl_Obj *)pc.clientData[0];

    return XOTclCDeallocMethod(interp, cl, object);

  }
}
  
static int
XOTclCInstFilterGuardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCInstFilterGuardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *filter = (char *)pc.clientData[0];
    Tcl_Obj *guard = (Tcl_Obj *)pc.clientData[1];

    return XOTclCInstFilterGuardMethod(interp, cl, filter, guard);

  }
}
  
static int
XOTclCInstForwardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCInstForwardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *method = (Tcl_Obj *)pc.clientData[0];
    Tcl_Obj *withDefault = (Tcl_Obj *)pc.clientData[1];
    int withEarlybinding = (int )pc.clientData[2];
    Tcl_Obj *withMethodprefix = (Tcl_Obj *)pc.clientData[3];
    int withObjscope = (int )pc.clientData[4];
    Tcl_Obj *withOnerror = (Tcl_Obj *)pc.clientData[5];
    int withVerbose = (int )pc.clientData[6];
    Tcl_Obj *target = (Tcl_Obj *)pc.clientData[7];

    return XOTclCInstForwardMethod(interp, cl, method, withDefault, withEarlybinding, withMethodprefix, withObjscope, withOnerror, withVerbose, target, objc-pc.lastobjc, objv+pc.lastobjc);

  }
}
  
static int
XOTclCInstMixinGuardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCInstMixinGuardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *mixin = (char *)pc.clientData[0];
    Tcl_Obj *guard = (Tcl_Obj *)pc.clientData[1];

    return XOTclCInstMixinGuardMethod(interp, cl, mixin, guard);

  }
}
  
static int
XOTclCInstParametercmdMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCInstParametercmdMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *name = (char *)pc.clientData[0];

    return XOTclCInstParametercmdMethod(interp, cl, name);

  }
}
  
static int
XOTclCInstProcMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCInstProcMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *name = (Tcl_Obj *)pc.clientData[0];
    Tcl_Obj *args = (Tcl_Obj *)pc.clientData[1];
    Tcl_Obj *body = (Tcl_Obj *)pc.clientData[2];
    Tcl_Obj *precondition = (Tcl_Obj *)pc.clientData[3];
    Tcl_Obj *postcondition = (Tcl_Obj *)pc.clientData[4];

    return XOTclCInstProcMethod(interp, cl, name, args, body, precondition, postcondition);

  }
}
  
static int
XOTclCInstProcMethodCStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCInstProcMethodCIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *name = (Tcl_Obj *)pc.clientData[0];
    Tcl_Obj *args = (Tcl_Obj *)pc.clientData[1];
    Tcl_Obj *body = (Tcl_Obj *)pc.clientData[2];
    Tcl_Obj *precondition = (Tcl_Obj *)pc.clientData[3];
    Tcl_Obj *postcondition = (Tcl_Obj *)pc.clientData[4];

    return XOTclCInstProcMethodC(interp, cl, name, args, body, precondition, postcondition);

  }
}
  
static int
XOTclCInvariantsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCInvariantsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *invariantlist = (Tcl_Obj *)pc.clientData[0];

    return XOTclCInvariantsMethod(interp, cl, invariantlist);

  }
}
  
static int
XOTclCNewMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCNewMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *withChildof = (XOTclObject *)pc.clientData[0];

    return XOTclCNewMethod(interp, cl, withChildof, objc-pc.lastobjc, objv+pc.lastobjc);

  }
}
  
static int
XOTclCRecreateMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCRecreateMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *name = (Tcl_Obj *)pc.clientData[0];

    return XOTclCRecreateMethod(interp, cl, name, objc, objv);

  }
}
  
static int
XOTclCUnknownMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclClass *cl =  XOTclObjectToClass(clientData);
  if (!cl) return XOTclObjErrType(interp, objv[0], "Class");
  if (parseObjv(interp, objc, objv, XOTclCUnknownMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *name = (char *)pc.clientData[0];

    return XOTclCUnknownMethod(interp, cl, name, objc, objv);

  }
}
  
static int
XOTclClassInfoHeritageMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoHeritageMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclClassInfoHeritageMethod(interp, class, pattern);

  }
}
  
static int
XOTclClassInfoInstancesMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstancesMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    int withClosure = (int )pc.clientData[1];
    char *patternString = NULL;
    XOTclObject *patternObj = NULL;
    Tcl_Obj *pattern = (Tcl_Obj *)pc.clientData[2];
    int returnCode;

    if (getMatchObject(interp, pattern,  objv[2], &patternObj, &patternString) == -1) {
      if (pattern) {
        DECR_REF_COUNT(pattern);
      }
      return TCL_OK;
    }
          
    returnCode = XOTclClassInfoInstancesMethod(interp, class, withClosure, patternString, patternObj);

    if (pattern) {
      DECR_REF_COUNT(pattern);
    }
    return returnCode;
  }
}
  
static int
XOTclClassInfoInstargsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstargsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclClassInfoInstargsMethod(interp, class, methodName);

  }
}
  
static int
XOTclClassInfoInstbodyMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstbodyMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclClassInfoInstbodyMethod(interp, class, methodName);

  }
}
  
static int
XOTclClassInfoInstcommandsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstcommandsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclClassInfoInstcommandsMethod(interp, class, pattern);

  }
}
  
static int
XOTclClassInfoInstdefaultMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstdefaultMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];
    char *arg = (char *)pc.clientData[2];
    Tcl_Obj *var = (Tcl_Obj *)pc.clientData[3];

    return XOTclClassInfoInstdefaultMethod(interp, class, methodName, arg, var);

  }
}
  
static int
XOTclClassInfoInstfilterMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstfilterMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    int withGuards = (int )pc.clientData[1];
    char *pattern = (char *)pc.clientData[2];

    return XOTclClassInfoInstfilterMethod(interp, class, withGuards, pattern);

  }
}
  
static int
XOTclClassInfoInstfilterguardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstfilterguardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *filter = (char *)pc.clientData[1];

    return XOTclClassInfoInstfilterguardMethod(interp, class, filter);

  }
}
  
static int
XOTclClassInfoInstforwardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstforwardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    int withDefinition = (int )pc.clientData[1];
    char *pattern = (char *)pc.clientData[2];

    return XOTclClassInfoInstforwardMethod(interp, class, withDefinition, pattern);

  }
}
  
static int
XOTclClassInfoInstinvarMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstinvarMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];

    return XOTclClassInfoInstinvarMethod(interp, class);

  }
}
  
static int
XOTclClassInfoInstmixinMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstmixinMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    int withClosure = (int )pc.clientData[1];
    int withGuards = (int )pc.clientData[2];
    char *patternString = NULL;
    XOTclObject *patternObj = NULL;
    Tcl_Obj *pattern = (Tcl_Obj *)pc.clientData[3];
    int returnCode;

    if (getMatchObject(interp, pattern,  objv[3], &patternObj, &patternString) == -1) {
      if (pattern) {
        DECR_REF_COUNT(pattern);
      }
      return TCL_OK;
    }
          
    returnCode = XOTclClassInfoInstmixinMethod(interp, class, withClosure, withGuards, patternString, patternObj);

    if (pattern) {
      DECR_REF_COUNT(pattern);
    }
    return returnCode;
  }
}
  
static int
XOTclClassInfoInstmixinguardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstmixinguardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *mixin = (char *)pc.clientData[1];

    return XOTclClassInfoInstmixinguardMethod(interp, class, mixin);

  }
}
  
static int
XOTclClassInfoInstmixinofMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstmixinofMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    int withClosure = (int )pc.clientData[1];
    char *patternString = NULL;
    XOTclObject *patternObj = NULL;
    Tcl_Obj *pattern = (Tcl_Obj *)pc.clientData[2];
    int returnCode;

    if (getMatchObject(interp, pattern,  objv[2], &patternObj, &patternString) == -1) {
      if (pattern) {
        DECR_REF_COUNT(pattern);
      }
      return TCL_OK;
    }
          
    returnCode = XOTclClassInfoInstmixinofMethod(interp, class, withClosure, patternString, patternObj);

    if (pattern) {
      DECR_REF_COUNT(pattern);
    }
    return returnCode;
  }
}
  
static int
XOTclClassInfoInstnonposargsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstnonposargsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclClassInfoInstnonposargsMethod(interp, class, methodName);

  }
}
  
static int
XOTclClassInfoInstparametercmdMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstparametercmdMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclClassInfoInstparametercmdMethod(interp, class, pattern);

  }
}
  
static int
XOTclClassInfoInstpostMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstpostMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclClassInfoInstpostMethod(interp, class, methodName);

  }
}
  
static int
XOTclClassInfoInstpreMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstpreMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclClassInfoInstpreMethod(interp, class, methodName);

  }
}
  
static int
XOTclClassInfoInstprocsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoInstprocsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclClassInfoInstprocsMethod(interp, class, pattern);

  }
}
  
static int
XOTclClassInfoMixinofMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoMixinofMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    int withClosure = (int )pc.clientData[1];
    char *patternString = NULL;
    XOTclObject *patternObj = NULL;
    Tcl_Obj *pattern = (Tcl_Obj *)pc.clientData[2];
    int returnCode;

    if (getMatchObject(interp, pattern,  objv[2], &patternObj, &patternString) == -1) {
      if (pattern) {
        DECR_REF_COUNT(pattern);
      }
      return TCL_OK;
    }
          
    returnCode = XOTclClassInfoMixinofMethod(interp, class, withClosure, patternString, patternObj);

    if (pattern) {
      DECR_REF_COUNT(pattern);
    }
    return returnCode;
  }
}
  
static int
XOTclClassInfoParameterMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoParameterMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];

    return XOTclClassInfoParameterMethod(interp, class);

  }
}
  
static int
XOTclClassInfoSlotsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoSlotsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];

    return XOTclClassInfoSlotsMethod(interp, class);

  }
}
  
static int
XOTclClassInfoSubclassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoSubclassMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    int withClosure = (int )pc.clientData[1];
    char *patternString = NULL;
    XOTclObject *patternObj = NULL;
    Tcl_Obj *pattern = (Tcl_Obj *)pc.clientData[2];
    int returnCode;

    if (getMatchObject(interp, pattern,  objv[2], &patternObj, &patternString) == -1) {
      if (pattern) {
        DECR_REF_COUNT(pattern);
      }
      return TCL_OK;
    }
          
    returnCode = XOTclClassInfoSubclassMethod(interp, class, withClosure, patternString, patternObj);

    if (pattern) {
      DECR_REF_COUNT(pattern);
    }
    return returnCode;
  }
}
  
static int
XOTclClassInfoSuperclassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclClassInfoSuperclassMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclClass *class = (XOTclClass *)pc.clientData[0];
    int withClosure = (int )pc.clientData[1];
    Tcl_Obj *pattern = (Tcl_Obj *)pc.clientData[2];

    return XOTclClassInfoSuperclassMethod(interp, class, withClosure, pattern);

  }
}
  
static int
XOTclObjInfoArgsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoArgsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclObjInfoArgsMethod(interp, object, methodName);

  }
}
  
static int
XOTclObjInfoBodyMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoBodyMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclObjInfoBodyMethod(interp, object, methodName);

  }
}
  
static int
XOTclObjInfoCheckMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoCheckMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];

    return XOTclObjInfoCheckMethod(interp, object);

  }
}
  
static int
XOTclObjInfoChildrenMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoChildrenMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclObjInfoChildrenMethod(interp, object, pattern);

  }
}
  
static int
XOTclObjInfoClassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoClassMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];

    return XOTclObjInfoClassMethod(interp, object);

  }
}
  
static int
XOTclObjInfoCommandsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoCommandsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclObjInfoCommandsMethod(interp, object, pattern);

  }
}
  
static int
XOTclObjInfoDefaultMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoDefaultMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];
    char *arg = (char *)pc.clientData[2];
    Tcl_Obj *var = (Tcl_Obj *)pc.clientData[3];

    return XOTclObjInfoDefaultMethod(interp, object, methodName, arg, var);

  }
}
  
static int
XOTclObjInfoFilterMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoFilterMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    int withOrder = (int )pc.clientData[1];
    int withGuards = (int )pc.clientData[2];
    char *pattern = (char *)pc.clientData[3];

    return XOTclObjInfoFilterMethod(interp, object, withOrder, withGuards, pattern);

  }
}
  
static int
XOTclObjInfoFilterguardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoFilterguardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *filter = (char *)pc.clientData[1];

    return XOTclObjInfoFilterguardMethod(interp, object, filter);

  }
}
  
static int
XOTclObjInfoForwardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoForwardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    int withDefinition = (int )pc.clientData[1];
    char *pattern = (char *)pc.clientData[2];

    return XOTclObjInfoForwardMethod(interp, object, withDefinition, pattern);

  }
}
  
static int
XOTclObjInfoHasnamespaceMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoHasnamespaceMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];

    return XOTclObjInfoHasnamespaceMethod(interp, object);

  }
}
  
static int
XOTclObjInfoInvarMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoInvarMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];

    return XOTclObjInfoInvarMethod(interp, object);

  }
}
  
static int
XOTclObjInfoMethodsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoMethodsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    int withNoprocs = (int )pc.clientData[1];
    int withNocmds = (int )pc.clientData[2];
    int withNomixins = (int )pc.clientData[3];
    int withIncontext = (int )pc.clientData[4];
    char *pattern = (char *)pc.clientData[5];

    return XOTclObjInfoMethodsMethod(interp, object, withNoprocs, withNocmds, withNomixins, withIncontext, pattern);

  }
}
  
static int
XOTclObjInfoMixinMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoMixinMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    int withGuards = (int )pc.clientData[1];
    int withOrder = (int )pc.clientData[2];
    char *patternString = NULL;
    XOTclObject *patternObj = NULL;
    Tcl_Obj *pattern = (Tcl_Obj *)pc.clientData[3];
    int returnCode;

    if (getMatchObject(interp, pattern,  objv[3], &patternObj, &patternString) == -1) {
      if (pattern) {
        DECR_REF_COUNT(pattern);
      }
      return TCL_OK;
    }
          
    returnCode = XOTclObjInfoMixinMethod(interp, object, withGuards, withOrder, patternString, patternObj);

    if (pattern) {
      DECR_REF_COUNT(pattern);
    }
    return returnCode;
  }
}
  
static int
XOTclObjInfoMixinguardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoMixinguardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *mixin = (char *)pc.clientData[1];

    return XOTclObjInfoMixinguardMethod(interp, object, mixin);

  }
}
  
static int
XOTclObjInfoNonposargsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoNonposargsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclObjInfoNonposargsMethod(interp, object, methodName);

  }
}
  
static int
XOTclObjInfoParametercmdMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoParametercmdMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclObjInfoParametercmdMethod(interp, object, pattern);

  }
}
  
static int
XOTclObjInfoParentMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoParentMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];

    return XOTclObjInfoParentMethod(interp, object);

  }
}
  
static int
XOTclObjInfoPostMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoPostMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclObjInfoPostMethod(interp, object, methodName);

  }
}
  
static int
XOTclObjInfoPreMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoPreMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];

    return XOTclObjInfoPreMethod(interp, object, methodName);

  }
}
  
static int
XOTclObjInfoPrecedenceMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoPrecedenceMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    int withIntrinsic = (int )pc.clientData[1];
    char *pattern = (char *)pc.clientData[2];

    return XOTclObjInfoPrecedenceMethod(interp, object, withIntrinsic, pattern);

  }
}
  
static int
XOTclObjInfoProcsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoProcsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclObjInfoProcsMethod(interp, object, pattern);

  }
}
  
static int
XOTclObjInfoSlotObjectsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoSlotObjectsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclObjInfoSlotObjectsMethod(interp, object, pattern);

  }
}
  
static int
XOTclObjInfoVarsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclObjInfoVarsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *pattern = (char *)pc.clientData[1];

    return XOTclObjInfoVarsMethod(interp, object, pattern);

  }
}
  
static int
XOTclOAutonameMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOAutonameMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    int withInstance = (int )pc.clientData[0];
    int withReset = (int )pc.clientData[1];
    Tcl_Obj *name = (Tcl_Obj *)pc.clientData[2];

    return XOTclOAutonameMethod(interp, obj, withInstance, withReset, name);

  }
}
  
static int
XOTclOCheckMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOCheckMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *flag = (Tcl_Obj *)pc.clientData[0];

    return XOTclOCheckMethod(interp, obj, flag);

  }
}
  
static int
XOTclOCleanupMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOCleanupMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclOCleanupMethod(interp, obj);

  }
}
  
static int
XOTclOConfigureMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOConfigureMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclOConfigureMethod(interp, obj, objc, objv);

  }
}
  
static int
XOTclODestroyMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclODestroyMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclODestroyMethod(interp, obj);

  }
}
  
static int
XOTclOExistsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOExistsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *var = (char *)pc.clientData[0];

    return XOTclOExistsMethod(interp, obj, var);

  }
}
  
static int
XOTclOFilterGuardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOFilterGuardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *filter = (char *)pc.clientData[0];
    Tcl_Obj *guard = (Tcl_Obj *)pc.clientData[1];

    return XOTclOFilterGuardMethod(interp, obj, filter, guard);

  }
}
  
static int
XOTclOFilterSearchMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOFilterSearchMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *filter = (char *)pc.clientData[0];

    return XOTclOFilterSearchMethod(interp, obj, filter);

  }
}
  
static int
XOTclOForwardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOForwardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *method = (Tcl_Obj *)pc.clientData[0];
    Tcl_Obj *withDefault = (Tcl_Obj *)pc.clientData[1];
    int withEarlybinding = (int )pc.clientData[2];
    Tcl_Obj *withMethodprefix = (Tcl_Obj *)pc.clientData[3];
    int withObjscope = (int )pc.clientData[4];
    Tcl_Obj *withOnerror = (Tcl_Obj *)pc.clientData[5];
    int withVerbose = (int )pc.clientData[6];
    Tcl_Obj *target = (Tcl_Obj *)pc.clientData[7];

    return XOTclOForwardMethod(interp, obj, method, withDefault, withEarlybinding, withMethodprefix, withObjscope, withOnerror, withVerbose, target, objc-pc.lastobjc, objv+pc.lastobjc);

  }
}
  
static int
XOTclOInstVarMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOInstVarMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclOInstVarMethod(interp, obj, objc, objv);

  }
}
  
static int
XOTclOInvariantsMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOInvariantsMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *invariantlist = (Tcl_Obj *)pc.clientData[0];

    return XOTclOInvariantsMethod(interp, obj, invariantlist);

  }
}
  
static int
XOTclOIsClassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOIsClassMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *class = (Tcl_Obj *)pc.clientData[0];

    return XOTclOIsClassMethod(interp, obj, class);

  }
}
  
static int
XOTclOIsMetaClassMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOIsMetaClassMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *metaclass = (Tcl_Obj *)pc.clientData[0];

    return XOTclOIsMetaClassMethod(interp, obj, metaclass);

  }
}
  
static int
XOTclOIsMixinMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOIsMixinMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *class = (Tcl_Obj *)pc.clientData[0];

    return XOTclOIsMixinMethod(interp, obj, class);

  }
}
  
static int
XOTclOIsObjectMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOIsObjectMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *object = (Tcl_Obj *)pc.clientData[0];

    return XOTclOIsObjectMethod(interp, obj, object);

  }
}
  
static int
XOTclOIsTypeMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOIsTypeMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *class = (Tcl_Obj *)pc.clientData[0];

    return XOTclOIsTypeMethod(interp, obj, class);

  }
}
  
static int
XOTclOMixinGuardMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOMixinGuardMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *mixin = (char *)pc.clientData[0];
    Tcl_Obj *guard = (Tcl_Obj *)pc.clientData[1];

    return XOTclOMixinGuardMethod(interp, obj, mixin, guard);

  }
}
  
static int
XOTclONextMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclONextMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclONextMethod(interp, obj, objc, objv);

  }
}
  
static int
XOTclONoinitMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclONoinitMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclONoinitMethod(interp, obj);

  }
}
  
static int
XOTclOParametercmdMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOParametercmdMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *name = (char *)pc.clientData[0];

    return XOTclOParametercmdMethod(interp, obj, name);

  }
}
  
static int
XOTclOProcMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOProcMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *name = (Tcl_Obj *)pc.clientData[0];
    Tcl_Obj *args = (Tcl_Obj *)pc.clientData[1];
    Tcl_Obj *body = (Tcl_Obj *)pc.clientData[2];
    Tcl_Obj *precondition = (Tcl_Obj *)pc.clientData[3];
    Tcl_Obj *postcondition = (Tcl_Obj *)pc.clientData[4];

    return XOTclOProcMethod(interp, obj, name, args, body, precondition, postcondition);

  }
}
  
static int
XOTclOProcSearchMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOProcSearchMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *name = (char *)pc.clientData[0];

    return XOTclOProcSearchMethod(interp, obj, name);

  }
}
  
static int
XOTclORequireNamespaceMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclORequireNamespaceMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclORequireNamespaceMethod(interp, obj);

  }
}
  
static int
XOTclOSetMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOSetMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    Tcl_Obj *var = (Tcl_Obj *)pc.clientData[0];
    Tcl_Obj *value = (Tcl_Obj *)pc.clientData[1];

    return XOTclOSetMethod(interp, obj, var, value);

  }
}
  
static int
XOTclOSetvaluesMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOSetvaluesMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclOSetvaluesMethod(interp, obj, objc, objv);

  }
}
  
static int
XOTclOUplevelMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOUplevelMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclOUplevelMethod(interp, obj, objc, objv);

  }
}
  
static int
XOTclOUpvarMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOUpvarMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclOUpvarMethod(interp, obj, objc, objv);

  }
}
  
static int
XOTclOVolatileMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOVolatileMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    

    return XOTclOVolatileMethod(interp, obj);

  }
}
  
static int
XOTclOVwaitMethodStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;
  XOTclObject *obj =  (XOTclObject *)clientData;
  if (!obj) return XOTclObjErrType(interp, objv[0], "Object");
  if (parseObjv(interp, objc, objv, XOTclOVwaitMethodIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    char *varname = (char *)pc.clientData[0];

    return XOTclOVwaitMethod(interp, obj, varname);

  }
}
  
static int
XOTclAliasCmdStub(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
  parseContext pc;

  if (parseObjv(interp, objc, objv, XOTclAliasCmdIdx, &pc) != TCL_OK) {
    return TCL_ERROR;
  } else {
    XOTclObject *object = (XOTclObject *)pc.clientData[0];
    char *methodName = (char *)pc.clientData[1];
    int withObjscope = (int )pc.clientData[2];
    int withPer_object = (int )pc.clientData[3];
    int withProtected = (int )pc.clientData[4];
    Tcl_Obj *cmdName = (Tcl_Obj *)pc.clientData[5];

    return XOTclAliasCmd(interp, object, methodName, withObjscope, withPer_object, withProtected, cmdName);

  }
}
  
static methodDefinition method_definitions[] = {
{"::xotcl::cmd::NonposArgs::type=boolean", XOTclCheckBooleanArgsStub, {
  {"name", 1, 0, NULL},
  {"value", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::NonposArgs::type=required", XOTclCheckRequiredArgsStub, {
  {"name", 1, 0, NULL},
  {"value", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::Class::alloc", XOTclCAllocMethodStub, {
  {"name", 1, 0, NULL}}
},
{"::xotcl::cmd::Class::create", XOTclCCreateMethodStub, {
  {"name", 1, 0, NULL},
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::Class::dealloc", XOTclCDeallocMethodStub, {
  {"object", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Class::instfilterguard", XOTclCInstFilterGuardMethodStub, {
  {"filter", 1, 0, NULL},
  {"guard", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Class::instforward", XOTclCInstForwardMethodStub, {
  {"method", 1, 0, "tclobj"},
  {"-default", 0, 1, "tclobj"},
  {"-earlybinding", 0, 0, NULL},
  {"-methodprefix", 0, 1, "tclobj"},
  {"-objscope", 0, 0, NULL},
  {"-onerror", 0, 1, "tclobj"},
  {"-verbose", 0, 0, NULL},
  {"target", 0, 0, "tclobj"},
  {"args", 0, 0, "args"}}
},
{"::xotcl::cmd::Class::instmixinguard", XOTclCInstMixinGuardMethodStub, {
  {"mixin", 1, 0, NULL},
  {"guard", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Class::instparametercmd", XOTclCInstParametercmdMethodStub, {
  {"name", 1, 0, NULL}}
},
{"::xotcl::cmd::Class::instproc", XOTclCInstProcMethodStub, {
  {"name", 1, 0, "tclobj"},
  {"args", 1, 0, "tclobj"},
  {"body", 1, 0, "tclobj"},
  {"precondition", 0, 0, "tclobj"},
  {"postcondition", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::Class::classscopedinstproc", XOTclCInstProcMethodCStub, {
  {"name", 1, 0, "tclobj"},
  {"args", 1, 0, "tclobj"},
  {"body", 1, 0, "tclobj"},
  {"precondition", 0, 0, "tclobj"},
  {"postcondition", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::Class::instinvar", XOTclCInvariantsMethodStub, {
  {"invariantlist", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Class::new", XOTclCNewMethodStub, {
  {"-childof", 0, 1, "object"},
  {"args", 0, 0, "args"}}
},
{"::xotcl::cmd::Class::recreate", XOTclCRecreateMethodStub, {
  {"name", 1, 0, "tclobj"},
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::Class::unknown", XOTclCUnknownMethodStub, {
  {"name", 1, 0, NULL},
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::ClassInfo::heritage", XOTclClassInfoHeritageMethodStub, {
  {"class", 1, 0, "class"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instances", XOTclClassInfoInstancesMethodStub, {
  {"class", 1, 0, "class"},
  {"-closure", 0, 0, NULL},
  {"pattern", 0, 0, "objpattern"}}
},
{"::xotcl::cmd::ClassInfo::instargs", XOTclClassInfoInstargsMethodStub, {
  {"class", 1, 0, "class"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instbody", XOTclClassInfoInstbodyMethodStub, {
  {"class", 1, 0, "class"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instcommands", XOTclClassInfoInstcommandsMethodStub, {
  {"class", 1, 0, "class"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instdefault", XOTclClassInfoInstdefaultMethodStub, {
  {"class", 1, 0, "class"},
  {"methodName", 1, 0, NULL},
  {"arg", 1, 0, NULL},
  {"var", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::ClassInfo::instfilter", XOTclClassInfoInstfilterMethodStub, {
  {"class", 1, 0, "class"},
  {"-guards", 0, 0, NULL},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instfilterguard", XOTclClassInfoInstfilterguardMethodStub, {
  {"class", 1, 0, "class"},
  {"filter", 1, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instforward", XOTclClassInfoInstforwardMethodStub, {
  {"class", 1, 0, "class"},
  {"-definition", 0, 0, NULL},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instinvar", XOTclClassInfoInstinvarMethodStub, {
  {"class", 1, 0, "class"}}
},
{"::xotcl::cmd::ClassInfo::instmixin", XOTclClassInfoInstmixinMethodStub, {
  {"class", 1, 0, "class"},
  {"-closure", 0, 0, NULL},
  {"-guards", 0, 0, NULL},
  {"pattern", 0, 0, "objpattern"}}
},
{"::xotcl::cmd::ClassInfo::instmixinguard", XOTclClassInfoInstmixinguardMethodStub, {
  {"class", 1, 0, "class"},
  {"mixin", 1, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instmixinof", XOTclClassInfoInstmixinofMethodStub, {
  {"class", 1, 0, "class"},
  {"-closure", 0, 0, NULL},
  {"pattern", 0, 0, "objpattern"}}
},
{"::xotcl::cmd::ClassInfo::instnonposargs", XOTclClassInfoInstnonposargsMethodStub, {
  {"class", 1, 0, "class"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instparametercmd", XOTclClassInfoInstparametercmdMethodStub, {
  {"class", 1, 0, "class"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instpost", XOTclClassInfoInstpostMethodStub, {
  {"class", 1, 0, "class"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instpre", XOTclClassInfoInstpreMethodStub, {
  {"class", 1, 0, "class"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::instprocs", XOTclClassInfoInstprocsMethodStub, {
  {"class", 1, 0, "class"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ClassInfo::mixinof", XOTclClassInfoMixinofMethodStub, {
  {"class", 1, 0, "class"},
  {"-closure", 0, 0, NULL},
  {"pattern", 0, 0, "objpattern"}}
},
{"::xotcl::cmd::ClassInfo::parameter", XOTclClassInfoParameterMethodStub, {
  {"class", 1, 0, "class"}}
},
{"::xotcl::cmd::ClassInfo::slots", XOTclClassInfoSlotsMethodStub, {
  {"class", 1, 0, "class"}}
},
{"::xotcl::cmd::ClassInfo::subclass", XOTclClassInfoSubclassMethodStub, {
  {"class", 1, 0, "class"},
  {"-closure", 0, 0, NULL},
  {"pattern", 0, 0, "objpattern"}}
},
{"::xotcl::cmd::ClassInfo::superclass", XOTclClassInfoSuperclassMethodStub, {
  {"class", 1, 0, "class"},
  {"-closure", 0, 0, NULL},
  {"pattern", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::ObjectInfo::args", XOTclObjInfoArgsMethodStub, {
  {"object", 1, 0, "object"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::body", XOTclObjInfoBodyMethodStub, {
  {"object", 1, 0, "object"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::check", XOTclObjInfoCheckMethodStub, {
  {"object", 1, 0, "object"}}
},
{"::xotcl::cmd::ObjectInfo::children", XOTclObjInfoChildrenMethodStub, {
  {"object", 1, 0, "object"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::class", XOTclObjInfoClassMethodStub, {
  {"object", 1, 0, "object"}}
},
{"::xotcl::cmd::ObjectInfo::commands", XOTclObjInfoCommandsMethodStub, {
  {"object", 1, 0, "object"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::default", XOTclObjInfoDefaultMethodStub, {
  {"object", 1, 0, "object"},
  {"methodName", 1, 0, NULL},
  {"arg", 1, 0, NULL},
  {"var", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::ObjectInfo::filter", XOTclObjInfoFilterMethodStub, {
  {"object", 1, 0, "object"},
  {"-order", 0, 0, NULL},
  {"-guards", 0, 0, NULL},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::filterguard", XOTclObjInfoFilterguardMethodStub, {
  {"object", 1, 0, "object"},
  {"filter", 1, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::forward", XOTclObjInfoForwardMethodStub, {
  {"object", 1, 0, "object"},
  {"-definition", 0, 0, NULL},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::hasnamespace", XOTclObjInfoHasnamespaceMethodStub, {
  {"object", 1, 0, "object"}}
},
{"::xotcl::cmd::ObjectInfo::invar", XOTclObjInfoInvarMethodStub, {
  {"object", 1, 0, "object"}}
},
{"::xotcl::cmd::ObjectInfo::methods", XOTclObjInfoMethodsMethodStub, {
  {"object", 1, 0, "object"},
  {"-noprocs", 0, 0, NULL},
  {"-nocmds", 0, 0, NULL},
  {"-nomixins", 0, 0, NULL},
  {"-incontext", 0, 0, NULL},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::mixin", XOTclObjInfoMixinMethodStub, {
  {"object", 1, 0, "object"},
  {"-guards", 0, 0, NULL},
  {"-order", 0, 0, NULL},
  {"pattern", 0, 0, "objpattern"}}
},
{"::xotcl::cmd::ObjectInfo::mixinguard", XOTclObjInfoMixinguardMethodStub, {
  {"object", 1, 0, "object"},
  {"mixin", 1, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::nonposargs", XOTclObjInfoNonposargsMethodStub, {
  {"object", 1, 0, "object"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::parametercmd", XOTclObjInfoParametercmdMethodStub, {
  {"object", 1, 0, "object"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::parent", XOTclObjInfoParentMethodStub, {
  {"object", 1, 0, "object"}}
},
{"::xotcl::cmd::ObjectInfo::post", XOTclObjInfoPostMethodStub, {
  {"object", 1, 0, "object"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::pre", XOTclObjInfoPreMethodStub, {
  {"object", 1, 0, "object"},
  {"methodName", 1, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::precedence", XOTclObjInfoPrecedenceMethodStub, {
  {"object", 1, 0, "object"},
  {"-intrinsic", 0, 0, NULL},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::procs", XOTclObjInfoProcsMethodStub, {
  {"object", 1, 0, "object"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::slotobjects", XOTclObjInfoSlotObjectsMethodStub, {
  {"object", 1, 0, "object"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::ObjectInfo::vars", XOTclObjInfoVarsMethodStub, {
  {"object", 1, 0, "object"},
  {"pattern", 0, 0, NULL}}
},
{"::xotcl::cmd::Object::autoname", XOTclOAutonameMethodStub, {
  {"-instance", 0, 0, NULL},
  {"-reset", 0, 0, NULL},
  {"name", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::check", XOTclOCheckMethodStub, {
  {"flag", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::cleanup", XOTclOCleanupMethodStub, {
  }
},
{"::xotcl::cmd::Object::configure", XOTclOConfigureMethodStub, {
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::Object::destroy", XOTclODestroyMethodStub, {
  }
},
{"::xotcl::cmd::Object::exists", XOTclOExistsMethodStub, {
  {"var", 1, 0, NULL}}
},
{"::xotcl::cmd::Object::filterguard", XOTclOFilterGuardMethodStub, {
  {"filter", 1, 0, NULL},
  {"guard", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::filtersearch", XOTclOFilterSearchMethodStub, {
  {"filter", 1, 0, NULL}}
},
{"::xotcl::cmd::Object::forward", XOTclOForwardMethodStub, {
  {"method", 1, 0, "tclobj"},
  {"-default", 0, 1, "tclobj"},
  {"-earlybinding", 0, 0, NULL},
  {"-methodprefix", 0, 1, "tclobj"},
  {"-objscope", 0, 0, NULL},
  {"-onerror", 0, 1, "tclobj"},
  {"-verbose", 0, 0, NULL},
  {"target", 0, 0, "tclobj"},
  {"args", 0, 0, "args"}}
},
{"::xotcl::cmd::Object::instvar", XOTclOInstVarMethodStub, {
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::Object::invar", XOTclOInvariantsMethodStub, {
  {"invariantlist", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::isclass", XOTclOIsClassMethodStub, {
  {"class", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::ismetaclass", XOTclOIsMetaClassMethodStub, {
  {"metaclass", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::ismixin", XOTclOIsMixinMethodStub, {
  {"class", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::isobject", XOTclOIsObjectMethodStub, {
  {"object", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::istype", XOTclOIsTypeMethodStub, {
  {"class", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::mixinguard", XOTclOMixinGuardMethodStub, {
  {"mixin", 1, 0, NULL},
  {"guard", 1, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::__next", XOTclONextMethodStub, {
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::Object::noinit", XOTclONoinitMethodStub, {
  }
},
{"::xotcl::cmd::Object::parametercmd", XOTclOParametercmdMethodStub, {
  {"name", 1, 0, NULL}}
},
{"::xotcl::cmd::Object::proc", XOTclOProcMethodStub, {
  {"name", 1, 0, "tclobj"},
  {"args", 1, 0, "tclobj"},
  {"body", 1, 0, "tclobj"},
  {"precondition", 0, 0, "tclobj"},
  {"postcondition", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::procsearch", XOTclOProcSearchMethodStub, {
  {"name", 1, 0, NULL}}
},
{"::xotcl::cmd::Object::requireNamespace", XOTclORequireNamespaceMethodStub, {
  }
},
{"::xotcl::cmd::Object::set", XOTclOSetMethodStub, {
  {"var", 1, 0, "tclobj"},
  {"value", 0, 0, "tclobj"}}
},
{"::xotcl::cmd::Object::setvalues", XOTclOSetvaluesMethodStub, {
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::Object::uplevel", XOTclOUplevelMethodStub, {
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::Object::upvar", XOTclOUpvarMethodStub, {
  {"args", 0, 0, "allargs"}}
},
{"::xotcl::cmd::Object::volatile", XOTclOVolatileMethodStub, {
  }
},
{"::xotcl::cmd::Object::vwait", XOTclOVwaitMethodStub, {
  {"varname", 1, 0, NULL}}
},
{"::xotcl::alias", XOTclAliasCmdStub, {
  {"object", 1, 0, "object"},
  {"methodName", 1, 0, NULL},
  {"-objscope", 0, 0, NULL},
  {"-per-object", 0, 0, NULL},
  {"-protected", 0, 0, NULL},
  {"cmdName", 1, 0, "tclobj"}}
}
};

