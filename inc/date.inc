<?php

class DateUtil {
  
  public static function getTimestamp($date) {

    if (DateUtil::isArrayDate($date)) {
      $date = mktime(0, 0 , 0,
        $date['month'],
        $date['day'],
        $date['year']);
    }

    return $date;
  }
  
  public static function isArrayDate($date) {
    return is_array($date) && isset($date['month']) && isset($date['day']) && isset($date['year']);
  }
  
  public static function getMicrosecondsOnDays($days) {
    return $days * 24 * 60 * 60;
  }
  
}