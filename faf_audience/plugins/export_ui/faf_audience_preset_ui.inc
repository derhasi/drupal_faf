<?php

/**
 * Export UI plugin for setting up FAF Audience sets and make them exportable
 * via UI.
 */


/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'faf_audience_preset',  // As defined in hook_schema().
  'access' => 'administer faf_audience',  // Define a permission users must have to access these pages.

  // Define the menu item.
  'menu' => array(
    'menu prefix' => 'admin/build/faf_audience',
    'menu item' => 'audience_preset',
    'menu title' => 'Audience Presets',
    'menu description' => 'Administer Audience presets.',
  ),

  // Define user interface texts.
  'title singular' => t('preset'),
  'title plural' => t('presets'),
  'title singular proper' => t('Audience preset'),
  'title plural proper' => t('Audience presets'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'faf_audience_preset_ctools_export_ui_form',
    'validate' => 'faf_audience_preset_ctools_export_ui_form_validate',
    // 'submit' and 'validate' are also valid callbacks.
  ),
);


/**
* Define the preset add/edit form.
*/
function faf_audience_preset_ctools_export_ui_form(&$form, &$form_state) {
  $preset = $form_state['item'];
  $audience_types = faf_audience_types_options_array('label');
  // Retrieve state of preset
  $new = !(isset($preset->name) && $preset->name);

  $form['audience_type'] = array(
    '#type' => 'select',
    '#title' => t('Audience Type'),
    '#description' => t('Select the audience type of this audience definition.'),
    '#default_value' => $preset->audience_type,
    '#options' => $audience_types,
    '#disabled' => !$new,
    '#required' => TRUE,
  );

  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('The human readable name or description of this preset.'),
    '#default_value' => $preset->description,
    '#required' => true,
  );


  // Show audience type specific description and form.
  if (isset($preset->audience_type)) {
    // Load type definition.
    $audience_type = faf_audience_get_type($preset->audience_type);

    // Audience type module seems to not be active. Alter description.
    if (!$audience_type) {
      $form['audience_type']['#description'] = '<span class="error">'.t('The given audience type "%audience_type" is not available. Please activate or update the module providing this audience type.', array('%audience_type' => $preset->audience_type)) .'</span>';
    }
    // Show Audience type forms and altered description
    else {
      $tvars = array(
        '%audience_label' => $audience_type['label'],
        '@audience_description' => $audience_type['description'],
        '%audience_type' => $audience_type['name'],
      );
      $form['audience_type']['#description'] = t('This preset is of type %audience_label [%audience_type]: @audience_description', $tvars);

      // Additional form for audience type.

      // Get selector options from array ...
      if (is_array($audience_type['selector options'])) {
        $selector_options = $audience_type['selector options'];
      }
      // ... or callback
      elseif ($selector_options_callback = ctools_plugin_get_function($audience_type, 'selector options')) {
        $selector_options = $selector_options_callback();
      }
      // else do not show a selector form element.
      else {
        $form['selector'] = NULL;
      }

      // Show select form element for selectore
      if (isset($selector_options)) {
        $form['selector'] = array(
          '#type' => 'select',
          '#title' => $audience_type['selector title'],
          '#description' => $audience_type['selector description'],
          '#options' => $selector_options,
          '#default_value' => $preset->selector,
          '#required' => TRUE,
        );
      }

      // @TODO: add additional configuration form.
    }
  }

}

/**
 * Validate faf_audience_preset settings form.
 */
function faf_audience_preset_ctools_export_ui_form_validate($form, &$form_state) {
  $values = $form_state['values'];

  // An existing preset needs an audience_type.
  if (empty($values['audience_type'])) {
    form_set_error('audience_type', t('There has to be a audience type selected!'));
  }
  // Does audience type definition exist?
  else {
    $res = faf_audience_get_type($values['audience_type']);
    if (empty($res)) {
      form_set_error('audience_type', t('The given audience type "%audience_type" is not available. Please activate or update the module providing this audience type.', array('%audience_type' => $values['audience_type'])));
    }
  }
}