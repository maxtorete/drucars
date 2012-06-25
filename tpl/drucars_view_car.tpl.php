<h1 id="page-title"><?php print $car->getModel() . ' - ' . $car->getModel(); ?></h1>
<?php if ($car->isRented()):?>
<h2><?php print t('This car is rented'); ?></h2>
<ul>
  <li><?php print t('Init date: @init_date', array('@init_date', date('d/m/Y', $car->getInitDate()))); ?></li>
  <li><?php print t('End date: @end_date', array('@end_date', date('d/m/Y', $car->getEndDate()))); ?></li>
</ul>
<?php endif;?>