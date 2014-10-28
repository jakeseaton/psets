<form action="add.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="amount">
                    <option value = "None">None</option>
                    <option value = "5.00">$5</option>
                    <option value = "10.00">$10</option>
                    <option value = "50.00">$50</option>
                    <option value = "100.00">$100</option>
                    <option value = "500.00">$500</option>
                    <option value = "1000.00">$1000</option>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">ADD!</button>
        </div>
    </fieldset>
    <div>
        <a href="javascript:history.go(-1);">Back to Portfolio</a>
    </div>
</form>