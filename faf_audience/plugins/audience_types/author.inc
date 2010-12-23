<?php
// $Id$

/**
 * @file
 *  provides the 'author' audience type to faf_audience.
 *
 *  The audience consists of the author of the given node, and/or the node
 *  editors (as stored in the node revisions table).
 */

$plugin = array(
  'label' => t('Author'),
  'description' => t('A single user can be declared as audience.'),
  'options' => array(
    'author' => t('Current author only'),
    'editor' => t('Editors only'),
  ),
  'options multiple' => TRUE,
);