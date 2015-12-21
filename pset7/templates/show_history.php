<table class="table table-striped">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>

    <tbody style="text-align: left;">
        <?php foreach($history as $hist): ?>
        <tr>
           <td><?= $hist["transaction"] ?></td>
           <td><?= $hist["time"] ?></td>
           <td><?= $hist["symbol"] ?></td>
           <td><?= $hist["shares"] ?></td>
           <td><?= $hist["price"] ?></td>
        </tr>
        <?php endforeach ?>
    </tbody>

</table>


