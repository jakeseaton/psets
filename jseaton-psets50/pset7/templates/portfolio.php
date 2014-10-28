
<div class="container">
            <ul class="nav nav-pills" style = "text-align: center">
                <li><a href="quote.php" >Quote</a></li>
                <li><a href="buy.php">Buy</a></li>
                <li><a href="sell.php">Sell</a></li>
                <li><a href="history.php">History</a></li>
                <li><a href="add.php">Add Cash</a></li>
                <li><a href="change_password.php">Change Password</a></li>
            </ul>

            <table class="table table-striped">

            <thead>
                <tr>
                    <th>Symbol</th>
                    <th>Name</th>
                    <th>Shares</th>
                    <th>Price</th>
                    <th>TOTAL</th>
                </tr>
            </thead>

            <tbody>

            <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td>$<?= $position["price"] ?></td>
                <td>$<?= $position["price"] * $position["shares"] ?></td>
            </tr>
            <? endforeach ?>
            <tr>
                <td>CASH</td>
                <td/>
                <td/>
                <td/>
                <td>$<?= number_format($cash[0]["cash"],2)?></td>
            </tr>

            </tbody>

            </table>
    </div>
    <div>
        <a href="logout.php"><strong>Log Out</strong></a>
    </div>
