<?php
// $Id$

/**
 * @file
 *  provides the 'author' audience type to audience.
 *
 *  The audience consists of the author of the given node, and/or the node
 *  editors (as stored in the node revisions table).
 */

$plugin = array(
  'label' => t('Author'),
  'description' => t('Declare node author and/or editors as audience.'),
  'is member callback' => '_audience_type_is_member_of_author',
  'selector options' => array(
    'author' => t('Current author only'),
    'editor' => t('Editors only'),
    'author or editor' => t('Author or editor'),
    'author and editor' => t('Author and editor'),
  ),
  'selector title' => t('Author / Editor'),
  'selector description' => t('Either author (the owner of the current node) and/or editors (node revision users) can be declared as audience preset.'),
);

/**
 * Callback function to specify if user is author or editor of the given context node.
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
function _audience_type_is_member_of_author($audience_preset, $account, $context = array()) {
  if (isset($context['node']) && is_object($context['node']) && $context['node']->nid) {
    $node = $context['node'];

    $selector = $audience_preset->selector;
    // Check on author
    if (($selector == 'author' || $selector == 'author or editor') && $node->uid == $account->uid) {
      return TRUE;
    }
    // Search revision information for editor selectors.
    elseif (strpos($selector, 'editor') !== FALSE) {
      $is_editor = db_result(db_query('SELECT uid FROM {node_revisions} WHERE nid = %d AND uid = %d', $node->nid, $account->uid));

      if ($selector == 'author and editor') {
        return ($is_editor && ($node->uid == $account->uid));
      }
      else {
        return $is_editor;
      }
    }
  }
  return FALSE;
}