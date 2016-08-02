# gtk
Simple usage for gtk in c++ simillar jquery with selector

This is an idea that we can develope it.

Now this is for gtk and after that we can write a class for qt and change our class name to our name and use that in gtk and qt and another windows manager kit ...

Compile it : 

```cli
g++ -std=c++11 `pkg-config --cflags gtk+-3.0` main.cpp -o hello `pkg-config --libs gtk+-3.0`
```

Simple usage :

```c++
    static Gtk window;
    window.init( &argc, &argv ).set_title( "test ast" ).set_size( 500, 150 );

    //window.body( "", )
    //window.load_html("index.html");
    
    //window.html("<button id='button_id' class='test'>Test ast</button>");
    
    typedef std::map <std::string, std::string> attr;
    
    //load css
    window.link( attr {
        { "href", "css.css" },
    });
    
    window.text("Result : asddddddddddddddddddd ",  attr { 
        { "class", "label" }, 
        { "id", "result" },
    } );
    

    //window("#result").html("test ast");
        
    window.br();
    
    window.label("Username : ",  attr { 
        { "class", "label" }, 
        { "id", "label1" },
    });


    window.input("username... ",  attr { 
        { "class", "input" }, 
        { "id", "username" },
    });
    
    window.br();

    window.label("Password : ",  attr { 
        { "class", "label" }, 
        { "id", "label2" },
    });

    window.input("password... ",  attr { 
        { "class", "input" }, 
        { "id", "password" },
    });


    
    window.button("Login",  attr { 
        { "class", "foo" }, 
        { "id", "button_id" },
    });
    
    window("#button_id").onclick([]() {
        std::cout << " button id clicked " << std::endl;
        std::cout << window("#username").val() << std::endl;
        std::cout << window("#password").val() << std::endl;
        
        window("#result").html( "username : "+ window("#username").val()+" password : "+window("#password").val() );
        
    });

```
