<?php

$defaults = array(
  'is member callback' => '_faf_privacy_audienc_is_member',
  'options multiple' => FALSE,
  'options values callback' => FALSE,
  'options form callback' => '_faf_privacy_audience_options_form',
  'options value callback' => '_faf_privacy_audience_options_get_value',

);


class privacy_audience_type {

  var $option_value = NULL;
  var $multiple = FALSE;

  function __construct($option_selection, $specs) {


  }

  function user_is_member($account) {

  }

  function option_values() {
    return array();
  }

  /**
   * Provide the form
   */
  function option_form() {
    $form['options'] = array(
      '#type' => 'select',
      '#default_value' => $this->option_value,
      '#multiple' => $this->multiple,
      '#options' => $this->option_values(),
      '#element_validate' =>
    );
    return $form;
  }

  /**
   *
   */
  function get_option_value($values) {
    if (isset($values['options'])) {
      return $values['options'];
    }
    return NULL;
  }
}