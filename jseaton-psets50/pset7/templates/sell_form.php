<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option value=""> </option>
                <?php foreach ($positions as $position): ?>
                    <option><?= $position["symbol"] ?></option>
                <? endforeach ?>
                    
             </select>
        </div>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="Shares" type="text"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
    <div>
        <a href="javascript:history.go(-1);">Back to Portfolio</a>
    </div>
</form>