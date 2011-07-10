<?php

/**
 * Template helper for theme_views_view_row_file
 */
function template_preprocess_views_view_row_file(&$vars) {
  $options = $vars['options'];

  // Make sure the variables are defined.
  $vars['file'] = '';
  $vars['comments'] = '';

  if (!empty($vars['row']->{$vars['field_alias']})) {
    $fid = $vars['row']->{$vars['field_alias']};
  }
  if (!is_numeric($fid)) {
    return;
  }

  $row_plugin = $vars['view']->style_plugin->row_plugin;
  $file = $row_plugin->files[$fid];

  if (empty($file)) {
    return;
  }

  $file->view = $vars['view'];
  // Detect which build module should be used.
  $file->view_mode = (!empty($options['view_mode'])) ? $options['view_mode'] : 'full';
  //@todo: need to work on view mode
  $content = file_view($file, $file->view_mode);
  if (!$options['links']) {
    unset($content['links']);
  }

  $vars['file'] = drupal_render($content);

}

