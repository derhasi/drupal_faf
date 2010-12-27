<?php
// $Id$

/**
 * @file
 *   provides the 'role' audience type to audience.
 */

$plugin = array(
  'label' => t('Audience Bundle: -AND-'),
  'description' => t('Check on a audience bundle in AND mode.'),
  'is member callback' => '_audience_type_is_member_of_audience_bundle_and',
  'selector title' => t('Audience Bundle'),
  'selector description' => t('Select an audience bundle defined on <em>!link</em>.', array('!link' => l('Audience Bundle Configuration', 'admin/build/audience/audience_bundles'))),
  'selector options' => 'audience_bundles_as_optionsarray',
);

/**
 * Callback function to specify if user is in ALL presets defined by the given
 * audience bundle.
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
function _audience_type_is_member_of_audience_bundle_and($audience_preset, $account, $context = array()) {
  $bundle_name = $audience_preset->selector;
  $bundle = audience_bundle_get_bundle($bundle_name);
  // User can only be member of a bundle if it exisits and has presets attached.
  if ($bundle && isset($bundle->presets) && is_array($bundle->presets) && count($bundle->presets)) {
    foreach ($bundle->presets as $preset_name) {
      $return = audience_is_member_of($preset_name, $account, $context);
      // Return false on failure, as user has to be member of ALL presets.
      if (!$return) {
        return FALSE;
      }
    }
    // If no one returned false, user is member of all presets defined.
    if ($return) {
      return TRUE;
    }
  }
  return FALSE;
}