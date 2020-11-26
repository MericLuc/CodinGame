while (true) 
{
    var maxH = -1;
    var resH = -1;

    for (let i = 0; i < 8; i++) 
    {
        const mountainH = parseInt(readline());

        if ( mountainH >= maxH ) { maxH = mountainH; resH = i; }
    }

    console.log(resH);
}