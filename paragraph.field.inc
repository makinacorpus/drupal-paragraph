<?php

/**
 * @file
 * Paragraph field definition.
 */

/**
 * Implements hook_field_info().
 */
function paragraph_field_info() {
  return array(
    'paragraph' => array(
      'label' => t("Paragraph"),
      'description' => t("Paragraph is a body with a title."),
      'settings' => array(),
      'instance_settings' => array(
        'allow_accordion' => false,
        'in_accordion' => false,
        'required_title' => true,
      ),
      'default_widget' => 'paragraph',
      'default_formatter' => 'paragraph',
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function paragraph_field_formatter_info() {
  return array(
    'paragraph' => array(
      'label' => t("Paragraph"),
      'description' => t("Display a paragraph."),
      'field types' => array('paragraph'),
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function paragraph_field_widget_info() {
  return array(
    'paragraph' => array(
      'label' => t("Paragraph"),
      'description' => t("Input a paragraph."),
      'field types' => array('paragraph'),
    ),
  );
}

/**
 * Implements hook_field_settings_form().
 */
function paragraph_field_instance_settings_form($field, $instance) {
  $form = array();
  $settings = $instance['settings'];

  switch ($field['type']) {

    case 'paragraph':
      $form['required_title'] = array(
        '#type' => 'checkbox',
        '#title' => t("Title is required"),
        '#default_value' => $settings['required_title'],
      );
      $form['allow_accordion'] = array(
        '#type' => 'checkbox',
        '#title' => t("User can set paragraph as being part of an accordion"),
        '#default_value' => $settings['allow_accordion'],
      );
      $form['in_accordion'] = array(
        '#type' => 'checkbox',
        '#title' => t("Paragraph are per default part of an accordion"),
        '#description' => t("This setting will be ignored if accordion is disabled."),
        '#default_value' => $settings['in_accordion'],
      );
      break;
  }

  return $form;
}

/**
 * Implements hook_field_formatter_view().
 */
function paragraph_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  switch ($display['type']) {

    case 'paragraph':
      list(,,$bundle) = entity_extract_ids($entity_type, $entity);
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'paragraph',
          '#item' => $item,
          '#langcode' => $langcode,
          '#entity_type' => $entity_type,
          '#bundle' => $bundle,
          '#field_name' => $field['field_name'],
        );
      }
      break;
  }

  return $element;
}

/**
 * Implements hook_field_widget_form().
 */
function paragraph_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  switch ($instance['widget']['type']) {

    case 'paragraph':

      $defaults = array();
      if (!empty($items[$delta])) {
        $defaults += $items[$delta];
      }
      $defaults += array(
        'title' => null,
        'value' => null,
        'format' => filter_default_format(),
        'in_accordion' => $instance['settings']['in_accordion'],
      );

      $element['title'] = array(
        '#type' => 'textfield',
        '#title' => t("Title"),
        '#default_value' => $defaults['title'],
        //'#required' => $instance['settings']['required_title'],
      );
      if ($instance['settings']['allow_accordion']) {
        $element['in_accordion'] = array(
          '#type' => 'checkbox',
          '#title' => t("Include in accordion"),
          '#default_value' => $defaults['in_accordion'],
        );
      }

      $element['#type'] = 'text_format';
      $element['#format'] = $defaults['format'];
      $element['#base_type'] = 'textarea';
      $element['#default_value'] = $defaults['value'];
      break;
  }

  return $element;
}

/**
 * Implements hook_field_is_empty().
 */
function paragraph_field_is_empty($item, $field) {
  return empty($item['value']);
}

/**
 * Implements template_preprocess_HOOK().
 */
function template_preprocess_paragraph(&$variables) {

  $item = $variables['item'];
  $variables['title'] = $item['title'];
  $variables['in_accordion'] = $item['in_accordion'];
  $variables['safe_value'] = check_markup($item['value'], $item['format'], $variables['langcode'], true);

  // Template suggestions.
  if ($variables['field_name']) {
    $variables['theme_hook_suggestions'][] = 'paragraph__' . $variables['field_name'];
  }
  if ($variables['entity_type']) {
    $variables['theme_hook_suggestions'][] = 'paragraph__' . $variables['entity_type'];
    if ($variables['field_name']) {
      $variables['theme_hook_suggestions'][] = 'paragraph__' . $variables['entity_type'] . '__' . $variables['field_name'];
    }
    if ($variables['bundle']) {
      $variables['theme_hook_suggestions'][] = 'paragraph__' . $variables['entity_type'] . '__' . $variables['bundle'];
      if ($variables['field_name']) {
        $variables['theme_hook_suggestions'][] = 'paragraph__' . $variables['entity_type'] . '__' . $variables['bundle'] . '__' . $variables['field_name'];
      }
    }
  }
}
