<?php foreach ($cars as $car): ?>
<h2><a href="<?php print url('drucars/' . $car->getCid()); ?>"><?php print $car->getLicensePlate() . ' - ' . $car->getModel(); ?></a></h2>
<?php endforeach; ?>
<?php print $pager; ?>