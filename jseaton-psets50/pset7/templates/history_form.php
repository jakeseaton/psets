<div class="container">
<table class="table table-striped">

    <thead>
        <tr>
            <th>Bought/Sold</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Date/Time</th>
        </tr>
    </thead>

    <tbody>
        <?php foreach($rows as $row): ?>
            <tr>
                <td><?= $row["type"] ?></td>
                <td><?= $row["symbol"] ?></td>
                <td><?= $row["amount"] ?></td>
                <td>$<?= number_format($row["price"], 2) ?></td>
                <td><?= $row["time"] ?></td>
            </tr>
            <? endforeach ?>
    </tbody>

</table>
    <div>
        <a href="javascript:history.go(-1);">Back to Portfolio</a>
    </div>
</div>

