<?php
/**
 * @file
 * Contains the term view row style plugin.
 */

/**
 * Plugin which performs a term_view on the resulting object.
 *
 * Most of the code on this object is in the theme function.
 */
class views_plugin_file_view extends views_plugin_row {
  // Basic properties that let the row style follow relationships.
  var $base_table = 'file_managed';
  var $base_field = 'fid';

  // Stores the terms loaded with pre_render.
  var $files = array();

  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    // Handle existing views with the deprecated 'teaser' option.
   // if (isset($this->options['teaser'])) {
   //   $this->options['build_mode'] = $this->options['teaser'] ? 'teaser' : 'full';
   // }
    // Handle existing views which has used build_mode instead of view_mode.
   // if (isset($this->options['build_mode'])) {
   //   $this->options['view_mode'] = $this->options['build_mode'];
  //  }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['view_mode'] = array('default' => 'teaser');
    $options['links'] = array('default' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = $this->options_form_summary_options();
    $form['view_mode'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('View mode'),
      '#default_value' => $this->options['view_mode'],
     );
    $form['links'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display links'),
      '#default_value' => $this->options['links'],
    );
  }

  /**
   * Return the main options, which are shown in the summary title.
   */
  function options_form_summary_options() {

    $entity_info = entity_get_info('file');
    $options = array();
    if (!empty($entity_info['view modes'])) {
      foreach ($entity_info['view modes'] as $mode => $settings) {
        $options[$mode] = $settings['label'];
      }
    }
    if (empty($options)) {
      $options = array(
        'teaser' => t('Teaser'),
        'full' => t('Full content')
      );
    }

    return $options;
  }

  function summary_title() {
    $options = $this->options_form_summary_options();
    return check_plain($options[$this->options['view_mode']]);
  }

  function pre_render($values) {
    $fids = array();
    foreach ($values as $row) {
      $fids[] = $row->{$this->field_alias};
    }
    $this->files = file_load_multiple($fids);
  }
}
