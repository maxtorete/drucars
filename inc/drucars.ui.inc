<?php

function drucars_main_page() {
  
  $cars = drucars_load_cars_with_pager();
  
  $output = theme('drucars_list_cars', array('cars' => $cars['cars'], 'pager' => $cars['pager']));
  
  return $output;
  
}

function drucars_view_car($cid) {
  
  $car = new Car($cid);
  $output = theme('drucars_view_car', array('car' => $car));
  
  return $output;
}

function drucars_edit_car_form($form, &$form_state, $cid = NULL) {

  $car = new Car($cid);

  if (!$car->isNew()) {
    $form['cid'] = array(
      '#type' => 'value',
      '#value' => $car->getCid(),
    );
  }

  $form['model'] = array(
    '#type' => 'textfield',
    '#title' => t('Model'),
    '#maxlenght' => 255,
    '#size' => 50,
    '#required' => TRUE,
    '#default_value' => $car->getModel(),
    '#description' => t('Brand and model of the car.'),
  );

  $form['license_plate'] = array(
    '#type' => 'textfield',
    '#title' => t('License Plate'),
    '#maxlenght' => 7,
    '#size' => 7,
    '#required' => TRUE,
    '#default_value' => $car->getLicensePlate(),
    '#description' => t('The license plate must has the spanish format (XXXXYYY).'),
  );

  $form['rented'] = array(
    '#title' => t('Rented?'),
    '#type' => 'checkbox',
    '#required' => FALSE,
    '#default_value' => $car->isRented(),
    '#description' => t('Check if the car is rented.'),
    '#ajax' => array(
      'wrapper' => 'group_rented_wrapper', 
      'callback' => 'drucars_rented_checkbox_callback',
    ),
  );

  $form['group_rented'] = array(
    '#prefix' => '<div id="group_rented_wrapper">',
    '#suffix' => '</div>',
  );

  if (!empty($form_state['values']['rented']) || !$form_state['rebuild'] && $car->isRented()) {
    $form['group_rented']['#type'] = 'fieldset';
    $form['group_rented']['#title'] = t('Renting dates');
    $form['group_rented']['#collapsible'] = TRUE;
    $form['group_rented']['#collapsed'] = FALSE;

    $init_date = getdate($car->getInitDate());

    $form['group_rented']['init_date'] = array(
      '#title' => t('Init date'),
      '#type' => 'date',
      '#required' => FALSE,
      '#default_value' => array(
        'year' => $init_date['year'],
        'month' => $init_date['mon'],
        'day' => $init_date['mday'],
    ),
      '#description' => t('Select the starting rent date.'),
    );

    $end_date = getdate($car->getEndDate());

    $form['group_rented']['end_date'] = array(
      '#title' => t('End date'),
      '#type' => 'date',
      '#required' => FALSE,
      '#default_value' => array(
        'year' => $end_date['year'],
        'month' => $end_date['mon'],
        'day' => $end_date['mday'],
    ),
      '#description' => t('Select the ending rent date.'),
    );

  }

  $form['send'] = array(
    '#type' => 'submit', 
    '#value' => t('Send'),
    '#states' => array(
      'enabled' => array(
        ':input[name="model"]' => array('filled' => TRUE),
        ':input[name="license_plate"]' => array('filled' => TRUE),
      ),
    ),
  );

  return $form;
}

function drucars_edit_car_form_validate($form, &$form_state) {

  if (!preg_match('/^[0-9]{4}[A-Z]{3}$/', $form_state['values']['license_plate'])) {
    form_set_error('license_plate', t('License plate must complain the spanish format: four numbers then three uppercase letters.'));
  }

  if (!empty($form_state['values']['rented'])) {

    $init_date = DateUtil::getTimestamp($form_state['values']['init_date']);
    $end_date = DateUtil::getTimestamp($form_state['values']['end_date']);

    if ($end_date < $init_date + DateUtil::getMicrosecondsOnDays(2)) {
      form_set_error('end_date', t('End date must be two days greater than init date.'));
    }
  }

}

function drucars_edit_car_form_submit($form, &$form_state) {

  if (form_get_errors()) {
    return $form;
  }

  $cid = isset($form_state['values']['cid']) ? $form_state['values']['cid'] : NULL;
  $car = new Car($cid);
  $car->loadPropertiesFromObject((Object)$form_state['values']);

  $car->save();

  drupal_set_message(t('Car saved successfully.'));

  $form_state['redirect'] = 'drucars/' . $car->getCid();

}

function drucars_delete_car_form($form, &$form_state, $cid) {
  $car = new Car($cid);

  $form['cid'] = array(
    '#type' => 'value', 
    '#value' => $cid,
  );
  
  $form['delete'] = array(
    '#type' => 'value', 
    '#value' => TRUE,
  );
  
  return confirm_form($form,
    NULL,
    'drucars/' . $cid,
    t('Are you sure you want to delete the car %car? This action cannot be undone',
      array('%car' => $car->getLicensePlate())),
    t('Delete'),
    t('Cancel'));
}

function drucars_delete_car_form_submit($form, &$form_state) {
  
  $cid = $form_state['values']['cid'];
  $car = new Car($cid);
  
  $car->delete();
  
  drupal_set_message(t('Car deleted successfully.'));
  
  $form_state['redirect'] = 'drucars';
}

function drucars_rented_checkbox_callback($form, $form_state) {
  return $form['group_rented'];
}