param($mode='start')

echo $mode
if ($mode -eq 'stop'){
kill -Name nginx
kill -Name nginx
kill -Name php* 
kill -Name php* 
ps nginx
ps php*
echo "stop"
}
elseif($mode -eq 'start'){

###########start nginx 
cd D:\nginx
start nginx.exe  -ArgumentList "-c  .\conf\nginx1.conf"

cd D:\wamp64\bin\php\php7.3.12

.\php-cgi-spawner.exe "php-cgi.exe -c php.ini" 9000 4 

cd $desktop

}