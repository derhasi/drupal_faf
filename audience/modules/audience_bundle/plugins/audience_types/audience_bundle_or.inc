<?php
// $Id$

/**
 * @file
 *   provides the 'role' audience type to audience.
 */

$plugin = array(
  'label' => t('Audience Bundle: -OR-'),
  'description' => t('Check on a audience bundle in OR mode.'),
  'is member callback' => '_audience_type_is_member_of_audience_bundle_or',
  'selector title' => t('Audience Bundle'),
  'selector description' => t('Select an audience bundle defined on <em>!link</em>.', array('!link' => l('Audience Bundle Configuration', 'admin/build/audience/audience_bundles'))),
  'selector options' => 'audience_bundles_as_optionsarray',
);

/**
 * Callback function to specify if user is in any preset defined be the audience
 * bundle.
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
function _audience_type_is_member_of_audience_bundle_or($audience_preset, $account, $context = array()) {
  $bundle_name = $audience_preset->selector;
  $bundle = audience_bundle_get_bundle($bundle_name);
  // User can only be member of a bundle if it exisits and has presets attached.
  if ($bundle && isset($bundle->presets) && is_array($bundle->presets)) {
    foreach ($bundle->presets as $preset_name) {
      $return = audience_is_member_of($preset_name, $account, $context);
      // Return true on success as the presets are ORed
      if ($return) {
        return TRUE;
      }
    }
  }
  return FALSE;
}