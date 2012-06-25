<?php

function drucars_main_page() {
  
  $cars = drucars_load_cars();
  
  $output = theme('drucars_list_cars', array('cars' => $cars['cars'], 'pager' => $cars['pager']));
  
  return $output;
  
}

function drucars_view_car($cid) {
  
  $car = new Car($cid);
  $output = theme('drucars_view_car', array('car' => $car));
  
  return $output;
}