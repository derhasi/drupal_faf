<?php
// $Id$

/**
 * @file
 *  provides the 'userrefernce' audience type to faf_audience.
 *
 *  The audience consists of users defined in the selected userreference field
 *  of the given node.
 */

if (module_exists('userreference')) {
  $plugin = array(
    'label' => t('Userreference Field'),
    'description' => t('Declare users of a userreference field as audience.'),
    'is member callback' => '_faf_audience_type_is_member_of_userreference',
    'selector options' => '_faf_audience_type_selector_options_userreference',
    'selector title' => t('Userreference Field'),
    'selector description' => t('Select the userreference field that shall define the audience for the then-given node.'),
  );
}

/**
 * Callback function to check if user is listed in the selected userreference
 * field of the given node.
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
function _faf_audience_type_is_member_of_userreference($audience_preset, $account, $context = array()) {
  if (isset($context['node']) && is_object($context['node']) && $context['node']->nid) {
    $node = $context['node'];

    $field_name = $audience_preset->selector;

    if (isset($node->$field_name) && is_array($node->$field_name)) {
      foreach ($node->$field_name as $item) {
        if ($item['uid'] == $account->uid) {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

/**
 * Helper function to retrieve the userrefernce fields.
 */
function _faf_audience_type_selector_options_userreference() {
  $fields = content_fields();
  $return = array();
  foreach ($fields as $name => $field) {
    if ($field['type'] == 'userreference') {
      $text = t('@field_name: @field_label', array('@field_label' => $field['widget']['label'], '@field_name' => $name));
      $text = (drupal_strlen($text) > 64) ? drupal_substr($text, 0, 64) .'...' : $text;
      $return[$name] = $text;
    }
  }
  ksort($return);
  return $return;
}
