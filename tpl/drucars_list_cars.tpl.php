<?php foreach ($cars as $car): ?>
<h2><a href="<?php print url('drucars/view/' . $car->getCid()); ?>"><?php print $car->getModel() . ' - ' . $car->getModel(); ?></a></h2>
<?php endforeach; ?>
<?php print $pager; ?>