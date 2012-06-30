<?php

class Car {
  
  private $cid;
  private $model;
  private $license_plate;
  private $rented;
  private $init_date;
  private $end_date;
  
  function __construct($cid = NULL) {
    $this->init();
    
    if (!empty($cid)) {
      $this->load($cid);
    }
  }
  
  function init() {
    $this->cid = null;
    $this->model = '';
    $this->license_plate = '';
    $this->rented = FALSE;
    $this->init_date = time();
    $this->end_date = time() + DateUtil::getMicrosecondsOnDays(2);
  }
  
  function load($cid) {
    
    $car = db_select('drucars','d')
      ->fields('d')
      ->condition('cid',$cid,'=')
      ->execute()
      ->fetchObject();
    
    $this->loadPropertiesFromObject($car);
  }
  
  function loadPropertiesFromObject($car) {
    
    if (isset($car->cid)) {
      $this->cid = $car->cid;
    }
    
    $this->model = $car->model;
    $this->license_plate = $car->license_plate;
    $this->rented = $car->rented;
    
    if (!empty($car->rented)) {
      $this->setInitDate($car->init_date);
      $this->setEndDate($car->end_date);
    }
    
  }
  
  function save() {
    $values['model'] = $this->model;
    $values['license_plate'] = $this->license_plate;
    $values['rented'] = $this->rented;
    $values['init_date'] = $this->init_date;
    $values['end_date'] = $this->end_date;
    
    if ($this->isNew()) {
      $this->cid = db_insert('drucars')
        ->fields($values)
        ->execute();
    }
    else {
      db_update('drucars')
        ->fields($values)
        ->condition('cid',$this->cid,'=')
        ->execute();
    }
  }
  
  function getCid() {
    return $this->cid;
  }
  
  function getModel() {
    return $this->model;
  }
  
  function setModel($model) {
    $this->model = $model;
  }
  
  function getLicensePlate() {
    return $this->license_plate;
  }
  
  function setLicensePlate($license_plate) {
    $this->license_plate = $license_plate;
  }
  
  function isRented() {
    return $this->rented;
  }
  
  function setRented($rented) {
    $this->rented = $rented;
  }
  
  function getInitDate() {
    return $this->init_date;
  }
  
  function setInitDate($init_date) { 
    $this->init_date = DateUtil::getTimestamp($init_date);
  }
  
  function getEndDate() {
    return $this->end_date;
  }
  
  function setEndDate($end_date) {
    $this->end_date = DateUtil::getTimestamp($end_date);
  }
  
  function isNew() {
    return empty($this->cid);
  }
  
}