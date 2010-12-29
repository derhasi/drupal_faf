<?php

/**
 * Export UI plugin for setting up Audience bundles and make them exportable
 * via UI.
 */


/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'audience_bundles',  // As defined in hook_schema().
  'access' => 'administer audience bundles',  // Define a permission users must have to access these pages.

  // Define the menu item.
  'menu' => array(
    'menu prefix' => 'admin/build/audience',
    'menu item' => 'audience_bundles',
    'menu title' => 'Audience bundles',
    'menu description' => 'Administer Audience bundles.',
  ),

  // Define user interface texts.
  'title singular' => t('bundle'),
  'title plural' => t('bundles'),
  'title singular proper' => t('Audience bundle'),
  'title plural proper' => t('Audience bundles'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'audience_bundle_ctools_export_ui_form',
    'validate' => 'audience_bundle_ctools_export_ui_form_validate',
    'submit' => 'audience_bundle_ctools_export_ui_form_submit',
    // 'submit' and 'validate' are also valid callbacks.
  ),
);


/**
* Define the bundle add/edit form.
*/
function audience_bundle_ctools_export_ui_form(&$form, &$form_state) {
  $bundle = $form_state['item'];
  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('The human readable name or description of this bundle.'),
    '#default_value' => $bundle->description,
    '#required' => true,
  );
  // Show select form element for selectore
  $form['presets'] = array(
    '#type' => 'select',
    '#title' => t('Audience presets'),
    '#description' => t('Select the audience presets to build a bundle with'),
    '#options' => audience_presets_as_optionsarray(TRUE),
    '#default_value' => $bundle->presets,
    '#multiple' => TRUE,
    '#required' => FALSE,
  );
}

/**
 * Validate audience_bundle settings form.
 */
function audience_bundle_ctools_export_ui_form_validate($form, &$form_state) {
  $values = $form_state['values'];

}
function audience_bundle_ctools_export_ui_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $form_state['item']->presets = $values['presets'];

}