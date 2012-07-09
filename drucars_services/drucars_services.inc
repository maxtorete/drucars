<?php

/**
 * @file
 * Contiene el negocio de las operaciones del servicio.
 */

/**
 *
 * Recomiendo realizar esta función a fin de devoler sólo los datos que son necesarios para los consumidores
 * de los servicios. Esta función recoge los valores necesarios de un objeto recibido como parámetro,
 * y devuelve un array asociativo donde los índices son self-explanatory :D
 * @param Car $car
 * @return array
 */

function _drucars_services_prepare_car($car) {
  return array (
    'cid' => $car->getCid(),
  	'model' => $car->getModel(),
  	'license_plate' => $car->getLicensePlate(),
  	'rented' => $car->isRented(),
  );
}


/**
 *
 * Negocio para la operación retrieve (CRUD)
 * @param integer $id
 * @return array
 */

function _drucars_services_retrieve($id) {
  $car = new Car($id);

  return _drucars_services_prepare_car($car);
}


/**
 *
 * Negocio para la operación index
 * @return array
 */

function _drucars_services_index() {
  $cars = drucars_load_cars();

  $output = array();

  foreach($cars as $c) {
  	$output[] = _drucars_services_prepare_car($c);
  }

  return $output;

}

/**
 *
 * Negocio para la operación rentAll tipo Action
 * @return array
 */
function _drucars_services_rentAll() {

  $output = true;

  foreach(drucars_load_cars() as $car) {
    $car->setRented(0);
  }

  return $output;
}


/**
*
* Negocio para la operación rent tipo Targeted Action
* @param integer $id
* @return array
*/

function _drucars_services_rent($id) {
  $car = new Car($id);
  $car->setRented(1);

  return _drucars_services_prepare_car($car);
}

/**
*
* Negocio para la operación unrent tipo Targeted Action
* @param integer $id
* @return array
*/

function _drucars_services_unrent($id) {
  $car = new Car($id);
  $car->setRented(0);

  return _drucars_services_prepare_car($car);
}


/**
*
* Negocio para la operación extras de tipo Relationships
* @param integer $id
* @return array
*/
function _drucars_services_extras($id) {
  return array(
    'Lunas tintadas',
    'Tubarro',
    'Climatizador bizona',
  );
}