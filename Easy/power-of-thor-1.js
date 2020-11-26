var inputs    = readline().split(' ');
var lightX    = parseInt(inputs[0]);
var lightY    = parseInt(inputs[1]);
var initialTX = parseInt(inputs[2]);
var initialTY = parseInt(inputs[3]);

while (true) 
{
    const remainingTurns = parseInt(readline());
    var direction = "";

    if      (initialTY < lightY) { initialTY++; direction = "S";  }        
    else if (initialTY > lightY) { initialTY--; direction = "N";  } 
            
    if      (initialTX < lightX) { initialTX++; direction += "E"; }       
    else if (initialTX > lightX) { initialTX--; direction += "W"; }

    console.log(direction);
}