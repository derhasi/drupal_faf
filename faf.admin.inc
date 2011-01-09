<?php
// $Id$


/**
 * @file
 *   Admin forms and theme functions.
 */

/**
 * Theme function to provide a draggable preset selection in FAF field settings.
 */
function theme_faf_audience_presets_selection($element) {
  if (!empty($element['#collapsible'])) {
    drupal_add_js('misc/collapse.js');

    if (!isset($element['#attributes']['class'])) {
      $element['#attributes']['class'] = '';
    }

    $element['#attributes']['class'] .= ' collapsible';
    if (!empty($element['#collapsed'])) {
      $element['#attributes']['class'] .= ' collapsed';
    }
  }

  $body = "";

  $children = element_children($element);

  $weight_header = "";
  drupal_add_tabledrag('faf-audience-presets-selection-table', 'order', 'sibling', 'faf-audience-preset-weight');

  $rows = array();
  foreach ($children as $key) {
    $element[$key]['weight']['#attributes']['class'] .= "faf-audience-preset-weight faf-audience-preset-weight-$key";
    if (!$weight_header) {
      $element[$key]['weight']['#title'];
    }
    unset($element[$key]['weight']['#title']);

    $weight = drupal_render($element[$key]['weight']);
    $rest = drupal_render($element[$key]);
    $rows[] = array(
      'data' => array($rest, $weight),
      'class' => 'draggable',
    );
  }

  $header = array(
    t('Audience preset'),
    $weight_header,
  );

  $body = theme('table', $header, $rows, array('id' => 'faf-audience-presets-selection-table'));

  return '<fieldset' . drupal_attributes($element['#attributes']) . '>' . ($element['#title'] ? '<legend>' . $element['#title'] . '</legend>' : '') . (isset($element['#description']) && $element['#description'] ? '<div class="description">' . $element['#description'] . '</div>' : '') . $body . (!empty($element['#children']) ? $element['#children'] : '') . (isset($element['#value']) ? $element['#value'] : '') . "</fieldset>\n";
}
