<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="symbol" placeholder="Symbol" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="Shares" type="text"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Buy</button>
        </div>
    </fieldset>
    <div>
        <a href="javascript:history.go(-1);">Back to Portfolio</a>
    </div>
</form>