<?php
// $Id$

/**
 * @file
 *   provides the 'role' audience type to faf_audience.
 */

$plugin = array(
  'label' => t('Role'),
  'description' => t('Declare a user role as audience.'),
  'is member callback' => '_faf_audience_type_is_member_of_role',
  'selector title' => t('User role'),
  'selector description' => t('Select a user role for to be the "audience".'),
  'selector options' => 'user_roles',
);

/**
 * Callback function to specify if user is in role selected by preset.
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
function _faf_audience_type_is_member_of_role($audience_preset, $account, $context = array()) {
  $audience_preset_role = $audience_preset->selector;
  return key_exists($account->uid, $account->roles);
}