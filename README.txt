; $Id$

@author: derhasi

Dependencies
============
ChaosTools: http://dru�al.org/project/ctools
Audience : http://github.com/derhasi/audience

Module description
==================
Field Access Field (faf.module) provides a cck field that can restrict access
rights on other fields of the same node. The node editor can select a predefined
audience (per select or checkboxes-widget) in the node add/edit form. The
selected audience then will be granted view permission on the field. For all
users that are not member of the audience, view permission will be denied.

If the field is not set as "required" in the field settings, there will be no
restriction on the pre-selected fields, when no audience is selected.

If the "dominant denial" setting is activated for a field in the field settings,
users for whom permissions are denied by this field, cannot be granted access by
another Field Access Field.

Audience definitions are provided by audience.module (currently on
https://github.com/derhasi/audience).

Field settings
==============

Required
--------
If checked, the user has to select an audience. If the field is not required,
empty values (or -no restriction-) means, that all users are granted access.

Number of values
----------------
On multiple selections, users are granted access if they are member of one of
the selected items. So audience selections are ORed within a field.

Fields
------
Select the fields view permissions shall be controlled by this field.

Audience presets
----------------
Select audience presets the user can select on node add/edit form. Audience
Presets are declared by audience module (admin/build/audience/presets).

Dominant denial
---------------
If selected, all permissions that are restricted by this field, cannot be
granted by another Field Access Field (or other hook_field_access
implementations).
Else access on a field is granted, if one or more field access fields grant
access and no other hook_field_access implementations deny access on the field.
So different Field Access Fields are ANDed, unless one uses "Dominant denial"

Similar modules
===============

CCK Privacy (drupal.org/project/privacy)
-----------
The module provides a setting for cck fields to be kept private or public.
Field Access Field will be merged into the 2.x-branch of that module.

Field Permissions
-----------------
That module is the successor of cck's content_permission module. But it only
provides per-role based permissions.
