<?php
// $Id$

/**
 * @file
 *   provides the 'user' audience type to audience.
 */

$plugin = array(
  'label' => t('User'),
  'description' => t('A single user can be declared as audience.'),
  'is member callback' => '_audience_type_is_member_of_user',
  'selector title' => t('User'),
  'selector description' => t('Select a user to be the "audience".'),
  'selector options' => '_audience_type_selector_options_user',
);

/**
 * Callback function to specify if user is the user defined in preset.
 *
 * @param $audience_preset
 *   the preset definition for the audience to check on.
 * @param $account
 *   the user object (at least as it is located in global $user) of the user to
 *   check against
 * @param $context
 *   an array of context objects, in a lot of cases this might be a node, given
 *   as array('node' => $node)
 */
function _audience_type_is_member_of_user($audience_preset, $account, $context = array()) {
  $audience_preset_user = $audience_preset->selector;
  return ($account->uid == $audience_preset_user);
}

/**
 * Callback function to retrieve all current users.
 */
function _audience_type_selector_options_user() {
  $users = &ctools_static(__FUNCTION__);

  if (empty($users)) {
    $users = array();
    $res = db_query("SELECT uid, name FROM {users} WHERE uid > 0 AND name<>'' ORDER BY name ASC");
    while ($obj = db_fetch_object($res)) {
      $users[$obj->uid] = $obj->name;
    }
  }
  return $users;
}