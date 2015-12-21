<div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tbody style="text-align: left;">
            <?php foreach ($positions as $position): ?>
                <tr>
                    <td><?= $position["symbol"] ?></td> 
                    <td><?= $position["shares"] ?></td> 
                    <td><?= $position["price"] ?></td>
                    <td><?= (float)($position["price"] * $position["shares"]) ?></td>
                </tr>
            <?php endforeach ?>
        </tbody>
    </table>
</div>

<div>
    Cash available: <?= $cash[0]["cash"] ?>
</div>
