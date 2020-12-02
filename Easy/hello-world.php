<?php
// Based on "TBali" solution
class GeoLocation
{
    public $lat = 0;
    public $long = 0;
    public $name = '';
    
    const Radius = 6371.0;
    
    public function __construct(string $_dms = 'N000000 E0000000', string $_name = '')
    {
        $this->name = $_name;
        $this->lat = floatval(substr($_dms, 1, 2)) + floatval(substr($_dms, 3, 2)) / 60 + floatval(substr($_dms, 5, 2)) / 3600;
        if ($_dms[0] == 'S')
            $this->lat = -1 * $this->lat;
        $this->long = floatval(substr($_dms, 9, 3)) + floatval(substr($_dms, 12, 2)) / 60 + floatval(substr($_dms, 14, 2)) / 3600;
        if ($_dms[8] == 'W')
            $this->long = -1 * $this->long;
    }

    public function getDistance(GeoLocation $otherLoc): int
    {
        $lat1rad = deg2rad($this->lat);
        $lat2rad = deg2rad($otherLoc->lat);
        $long1rad = deg2rad($this->long);
        $long2rad = deg2rad($otherLoc->long);
        $delta = acos(sin($lat1rad) * sin($lat2rad) + cos($lat1rad) * cos($lat2rad) * cos(abs($long1rad - $long2rad)));
        return intval(round($delta * self::Radius));
    }

    public function toString(): string
    {
        $latVal = abs($this->lat);
        $latDeg = floor($latVal);
        $latMin = floor(($latVal - $latDeg) * 60);
        $latSec = round(($latVal - $latDeg - $latMin / 60) * 3600);
        $ans = (($this->lat >= 0) ? 'N' : 'S');
        $ans .= str_pad(strval(intval($latDeg)), 2, '0', STR_PAD_LEFT);
        $ans .= str_pad(strval(intval($latMin)), 2, '0', STR_PAD_LEFT);
        $ans .= str_pad(strval(intval($latSec)), 2, '0', STR_PAD_LEFT);
        $ans .= ' ';
        $longVal = abs($this->long);
        $longDeg = floor($longVal);
        $longMin = floor(($longVal - $longDeg) * 60);
        $longSec = round(($longVal - $longDeg - $longMin / 60) * 3600);
        $ans .= (($this->long >= 0) ? 'E' : 'W');
        $ans .= str_pad(strval(intval($longDeg)), 3, '0', STR_PAD_LEFT);
        $ans .= str_pad(strval(intval($longMin)), 2, '0', STR_PAD_LEFT);
        $ans .= str_pad(strval(intval($longSec)), 2, '0', STR_PAD_LEFT);
        return $ans;
    }

    public function getMidPoint(GeoLocation $otherLoc): GeoLocation
    {  
        $lat1rad = deg2rad($this->lat);
        $long1rad = deg2rad($this->long);
        $lat2rad = deg2rad($otherLoc->lat);
        $long2rad = deg2rad($otherLoc->long);
        $Bx = cos($lat2rad) * cos($long2rad - $long1rad);
        $By = cos($lat2rad) * sin($long2rad - $long1rad);
        $p = new Geolocation();
        $p->lat = rad2deg(atan2(sin($lat1rad) + sin($lat2rad), sqrt((cos($lat1rad) + $Bx) * (cos($lat1rad) + $Bx) + $By * $By)));
        $p->long = rad2deg($long1rad + atan2($By, cos($lat1rad) + $Bx));
        return $p;    
    }  
}

fscanf(STDIN, "%d", $n );
fscanf(STDIN, "%d", $m) ;

for ($i = 0; $i < $n; $i++)
{
    $line = explode(' ', stream_get_line(STDIN, 48 + 1, "\n"));
    $capitals[] = new GeoLocation($line[1] . ' ' . $line[2], $line[0]);
}

for ($i = 0; $i < $n; $i++)
{
    $message[$i] = stream_get_line(STDIN, 128 + 1, "\n");
}

for ($i = 0; $i < $m; $i++)
{
    $line = stream_get_line(STDIN, 16 + 1, "\n");
    $travels[] = new GeoLocation($line);
}
foreach ($travels as $idxTravel => $travel)
{
    $cd = PHP_INT_MAX;
    $cidx = array();
    foreach ($capitals as $idxCapital => $capital)
    {
        $dst = $travel->getDistance($capital);
        if ($dst < $cd)
        {
            $cd = $dst;
            $cidx = [$idxCapital];
        }
        elseif ($dst == $cd)
            $cidx[] = $idxCapital;
    }
    $answer = '';
    for ($i = 0; $i < count($cidx); $i++)
    {
        if ($i > 0)
            $answer .= ' ';
        $answer .= $message[$cidx[$i]];
    }

    echo $answer . "\n";
}
?>