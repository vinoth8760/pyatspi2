#define MAX_ROLES 100

static char *role_names [MAX_ROLES] =
{
  " ",
  "accelerator label",
  "alert",
  "animation",
  "arrow",
  "calendar",
  "canvas",
  "check box",
  "menu item",
  "color chooser",
  "column header",
  "combo box",
  "date editor",
  "desktop icon",
  "desktop frame",
  "dial",
  "dialog",
  "directory pane",
  "drawing area",
  "file chooser",
  "filler",
  "font chooser",
  "frame",
  "glass pane",
  "HTML container",
  "icon",
  "image",
  "internal frame",
  "label",
  "layered pane",
  "list",
  "list item",
  "menu",
  "menubar",
  "menu item",
  "option pane",
  "page tab",
  "page tab list",
  "panel",
  "password text",
  "popup menu",
  "progress bar",
  "pushbutton",
  "radiobutton",
  "radio menu item",
  "root pane",
  "row header",
  "scrollbar",
  "scrollpane",
  "separator",
  "slider",
  "split pane",
  "spin button",
  "status bar",
  "table",
  "table cell",
  "table column header",
  "table row header",
  "tearoff menu item",
  "text",
  "toggle button",
  "toolbar",
  "tooltip",
  "tree",
  " ",
  "viewport",
  "window",
};

/*
 * Returns a localizable string name for an AtkRole enumerated type.
 */
char*
Accessible_Role_getName (Accessibility_Role role)
{
  if (role < MAX_ROLES) return role_names [(int) role];
  else return "";
}



/**
 * Accessible_ref:
 * @obj: a pointer to the #Accessible object on which to operate.
 *
 * Increment the reference count for an #Accessible object.
 *
 * Returns: (no return code implemented yet).
 *
 **/
int
Accessible_ref (Accessible *obj)
{
  Accessibility_Accessible_ref (*obj, &ev);
  return 0;
}


/**
 * Accessible_unref:
 * @obj: a pointer to the #Accessible object on which to operate.
 *
 * Decrement the reference count for an #Accessible object.
 *
 * Returns: (no return code implemented yet).
 *
 **/
int
Accessible_unref (Accessible *obj)
{
  Accessibility_Accessible_unref (*obj, &ev);
  return 0;
}

/**
 * Accessible_getName:
 * @obj: a pointer to the #Accessible object on which to operate.
 *
 * Get the name of an #Accessible object.
 *
 * Returns: a UTF-8 string indicating the name of the #Accessible object.
 *
 **/
char *
Accessible_getName (Accessible *obj)
{
  return (char *)
    Accessibility_Accessible__get_name (*obj, &ev);
}

/**
 * Accessible_getDescription:
 * @obj: a pointer to the #Accessible object on which to operate.
 *
 * Get the description of an #Accessible object.
 *
 * Returns: a UTF-8 string describing the #Accessible object.
 *
 **/
char *
Accessible_getDescription (Accessible *obj)
{
  return (char *)
    Accessibility_Accessible__get_description (*obj, &ev);
}

/**
 * Accessible_getParent:
 * @obj: a pointer to the #Accessible object to query.
 *
 * Get an #Accessible object's parent container.
 *
 * Returns: a pointer to the #Accessible object which contains the given
 *          #Accessible instance, or NULL if the @obj has no parent container.
 *
 **/
Accessible *
Accessible_getParent (Accessible *obj)
{
  return Obj_Add (Accessibility_Accessible__get_parent (*obj, &ev));
}

/**
 * Accessible_getChildCount:
 *
 * @obj: a pointer to the #Accessible object on which to operate.
 *
 * Get the number of children contained by an #Accessible object.
 *
 * Returns: a #long indicating the number of #Accessible children
 *          contained by an #Accessible object.
 *
 **/
long
Accessible_getChildCount (Accessible *obj)
{
  return Accessibility_Accessible__get_childCount (*obj, &ev);
}

/**
 * Accessible_getChildAtIndex:
 *
 * @obj: a pointer to the #Accessible object on which to operate.
 * @childIndex: a #long indicating which child is specified.
 *
 * Get the #Accessible child of an #Accessible object at a given index.
 *
 * Returns: a pointer to the #Accessible child object at index
 *          @childIndex.
 *
 **/
Accessible *
Accessible_getChildAtIndex (Accessible *obj,
                            long childIndex)
{
  return Obj_Add (Accessibility_Accessible_getChildAtIndex (*obj, childIndex, &ev));
}

/**
 * Accessible_getIndexInParent:
 *
 * @obj: a pointer to the #Accessible object on which to operate.
 *
 * Get the index of an #Accessible object in its containing #Accessible.
 *
 * Returns: a #long indicating the index of the #Accessible object
 *          in its parent (i.e. containing) #Accessible instance,
 *          or -1 if @obj has no containing parent.
 *
 **/
long
Accessible_getIndexInParent (Accessible *obj)
{
  return Accessibility_Accessible_getIndexInParent (*obj, &ev);
}

/**
 * Accessible_getRelationSet:
 *
 * Not Yet Implemented.
 *
 * Returns: a pointer to an array of #AccessibleRelations.
 *
 **/
AccessibleRelation **
Accessible_getRelationSet (Accessible *obj)
{
  return NULL;
}

/**
 * Accessible_getRole:
 * @obj: a pointer to the #Accessible object on which to operate.
 *
 * Get the UI role of an #Accessible object.
 *
 * Returns: a UTF-8 string indicating the UI role of the #Accessible object.
 *
 **/
char *
Accessible_getRole (Accessible *obj)
{
  return Accessible_Role_getName (
		  Accessibility_Accessible_getRole (*obj, &ev));
}

/**
 * Accessible_getStateSet:
 *
 * Not Yet Implemented.
 *
 * Returns: a pointer to an #AccessibleStateSet representing the object's current state.
 **/
AccessibleStateSet *
Accessible_getStateSet (Accessible *obj)
{
  return NULL;
}

/* Interface query methods */

/**
 * Accessible_isAction:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Query whether the specified #Accessible implements #AccessibleAction.
 * Not Yet Implemented.
 *
 * Returns: #TRUE if @obj implements the #AccessibleAction interface,
 *          #FALSE otherwise.
 **/
boolean
Accessible_isAction (Accessible *obj)
{
  Bonobo_Unknown iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Action:1.0",
                                             &ev);
  return (iface != NULL) ? TRUE : FALSE;
}

/**
 * Accessible_isComponent:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Query whether the specified #Accessible implements #AccessibleComponent.
 *
 * Returns: #TRUE if @obj implements the #AccessibleComponent interface,
 *          #FALSE otherwise.
 **/
boolean
Accessible_isComponent (Accessible *obj)
{
  Bonobo_Unknown iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Component:1.0",
                                             &ev);
  return (iface != NULL) ? TRUE : FALSE;
}

/**
 * Accessible_isEditableText:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Query whether the specified #Accessible implements #AccessibleEditableText.
 * Not Yet Implemented.
 *
 * Returns: #TRUE if @obj implements the #AccessibleEditableText interface,
 *          #FALSE otherwise.
 **/
boolean
Accessible_isEditableText (Accessible *obj)
{
  Bonobo_Unknown iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/EditableText:1.0",
                                             &ev);
  return (iface != NULL) ? TRUE : FALSE;
}

/**
 * Accessible_isHypertext:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Query whether the specified #Accessible implements #AccessibleHypertext.
 * Not Yet Implemented.
 *
 * Returns: #TRUE if @obj implements the #AccessibleHypertext interface,
 *          #FALSE otherwise.
 **/
boolean
Accessible_isHypertext (Accessible *obj)
{
  Bonobo_Unknown iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Hypertext:1.0",
                                             &ev);
  return (iface != NULL) ? TRUE : FALSE;
}

/**
 * Accessible_isImage:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Query whether the specified #Accessible implements #AccessibleImage.
 * Not Yet Implemented.
 *
 * Returns: #TRUE if @obj implements the #AccessibleImage interface,
 *          #FALSE otherwise.
**/
boolean
Accessible_isImage (Accessible *obj)
{
  Bonobo_Unknown iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Image:1.0",
                                             &ev);
  return (iface != NULL) ? TRUE : FALSE;
}

/**
  * Accessible_isSelection:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Query whether the specified #Accessible implements #AccessibleSelection.
 * Not Yet Implemented.
 *
 * Returns: #TRUE if @obj implements the #AccessibleSelection interface,
 *          #FALSE otherwise.
**/
boolean
Accessible_isSelection (Accessible *obj)
{
  Bonobo_Unknown iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Selection:1.0",
                                             &ev);
  return (iface != NULL) ? TRUE : FALSE;
}

/**
 * Accessible_isTable:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Query whether the specified #Accessible implements #AccessibleTable.
 * Not Yet Implemented.
 *
 * Returns: #TRUE if @obj implements the #AccessibleTable interface,
 *          #FALSE otherwise.
**/
boolean
Accessible_isTable (Accessible *obj)
{
  Bonobo_Unknown iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Table:1.0",
                                             &ev);
  return (iface != NULL) ? TRUE : FALSE;
}

/**
 * Accessible_isText:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Query whether the specified #Accessible implements #AccessibleText.
 * Not Yet Implemented.
 *
 * Returns: #TRUE if @obj implements the #AccessibleText interface,
 *          #FALSE otherwise.
**/
boolean
Accessible_isText (Accessible *obj)
{
  Bonobo_Unknown iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Text:1.0",
                                             &ev);
  return (iface != NULL) ? TRUE : FALSE;
}

/**
 * Accessible_getAction:
 *
 * Not Yet Implemented.
 *
 **/
AccessibleAction *
Accessible_getAction (Accessible *obj)
{
  AccessibleComponent iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Action:1.0",
                                             &ev);
  return Obj_Add (iface);
}

/**
 * Accessible_getComponent:
 * @obj: a pointer to the #Accessible instance to query.
 *
 * Get the #AccessibleComponent interface for an #Accessible.
 *
 * Returns: a pointer to an #AccessibleComponent interface instance, or
 *          NULL if @obj does not implement #AccessibleComponent.
 **/
AccessibleComponent *
Accessible_getComponent (Accessible *obj)
{
  AccessibleComponent iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Component:1.0",
                                             &ev);
  return Obj_Add (iface);
}

AccessibleEditableText *
Accessible_getEditableText (Accessible *obj)
{
  AccessibleComponent iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/EditableText:1.0",
                                             &ev);
  return Obj_Add (iface);
}



AccessibleHypertext *
Accessible_getHypertext (Accessible *obj)
{
  AccessibleComponent iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Hypertext:1.0",
                                             &ev);
  return Obj_Add (iface);
}



AccessibleImage *
Accessible_getImage (Accessible *obj)
{
  AccessibleImage iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Image:1.0",
                                             &ev);
  return Obj_Add (iface);
}



AccessibleSelection *
Accessible_getSelection (Accessible *obj)
{
  AccessibleSelection iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Selection:1.0",
                                             &ev);
  return Obj_Add (iface);
}



AccessibleTable *
Accessible_getTable (Accessible *obj)
{
  AccessibleTable iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Table:1.0",
                                             &ev);
  return Obj_Add (iface);
}



AccessibleText *
Accessible_getText (Accessible *obj)
{
  AccessibleText iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Text:1.0",
                                             &ev);
  return Obj_Add (iface);
}



AccessibleValue *
Accessible_getValue (Accessible *obj)
{
  AccessibleComponent iface =
    Accessibility_Accessible_queryInterface (*obj,
                                             "IDL:Accessibility/Value:1.0",
                                             &ev);
  return Obj_Add (iface);
}



/**
 * Accessible_queryInterface:
 * @obj: a pointer to the #Accessible instance to query.
 * @interface_name: a UTF-8 character string specifiying the requested interface.
 *
 * Query an #Accessible object to for a named interface.
 *
 * Returns: an instance of the named interface object, if it is implemented
 *          by @obj, or NULL otherwise.
 *
 **/
GenericInterface *
Accessible_queryInterface (Accessible *obj, char *interface_name)
{
  GenericInterface iface;
  iface = Accessibility_Accessible_queryInterface (*obj,
                                                    interface_name,
                                                    &ev);
  return (iface != NULL) ? Obj_Add (iface) : NULL;
}
