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
    'menu item' => 'faf_audience_preset',
    'menu title' => 'Audience',
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
    // 'submit' and 'validate' are also valid callbacks.
  ),
);


/**
* Define the preset add/edit form.
*/
function faf_audience_preset_ctools_export_ui_form(&$form, &$form_state) {
  $preset = $form_state['item'];
  _faf_audience_validate_preset($preset, TRUE);

dpm($preset);
  $audience_types = faf_audience_types_options_array('label');

  // Retrieve state of
  $new = !(isset($preset->name) && $preset->name);

  // Creating
  $form['atype'] = array(
    '#type' => 'select',
    '#title' => t('Audience Type'),
    '#description' => t('Select the audience type, this audience definition shall be specified by.'),
    '#default_value' => NULL,
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


  // Add Mymodule's configuration interface.
  $form['config'] = array(
    '#type' => 'textfield',
    '#title' => t('Mymodule configuration'),
    '#description' => t('This is just the simplest possible example of a configuration interface.'),
    '#default_value' => $preset->config,
    '#required' => false,
  );

}

?>