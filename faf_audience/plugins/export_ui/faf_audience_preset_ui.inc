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

  // Show description of audience type if it is given
  // or show error description if module is not available
  if (isset($preset->audience_type)) {
    $audience_type = faf_audience_get_type($preset->audience_type);
    // Show Audience type and description
    if ($audience_type) {
      $tvars = array(
        '%audience_label' => $audience_type['label'],
        '@audience_description' => $audience_type['description'],
        '%audience_type' => $audience_type['name'],
      );
      $audience_type_description = t('This preset is of type %audience_label [%audience_type]: @audience_description', $tvars);
    }
    // Else audience type module seems to not be active.
    else {
      $audience_type_description = '<span class="error">'.t('The given audience type "%audience_type" is not available. Please activate or update the module providing this audience type.', array('%audience_type' => $preset->audience_type)) .'</span>';
    }
  }
  else {
    $audience_type_description = t('Select the audience type of this audience definition.');
  }

  $form['audience_type'] = array(
    '#type' => 'select',
    '#title' => t('Audience Type'),
    '#description' => $audience_type_description,
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

  // Add audience type specific forms
  if (!$new && $audience_type) {

    // Add Mymodule's configuration interface.
    $form['config'] = array(
      '#type' => 'textfield',
      '#title' => t('Mymodule configuration'),
      '#description' => t('This is just the simplest possible example of a configuration interface.'),
      '#default_value' => $preset->config,
      '#required' => false,
    );
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