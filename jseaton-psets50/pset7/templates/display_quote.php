<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

                    <title>C$50 Finance: Quote</title>
        
        <script src="/js/jquery-1.10.2.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="middle">
                A share of <?=$name?> (<?=$symbol?>) costs <strong><?=$price?></strong>.
            </div>
            <div>
                <a href="javascript:history.go(-1);">Back</a>
            </div>
        </div>

    </body>

</html>