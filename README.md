# gtk
Simple usage for gtk in c++ simillar jquery with selector

This is an idea and can developed by us.

Now this is for gtk and after that we can write a class for qt and change our class name to our name and use that in gtk and qt and another windows manager kit ...

Simple usage :

```c++
    Gtk window;
    window.init( &argc, &argv ).set_title( "test ast" ).set_size( 200, 200 );

    //window.html("<button id='button_id' class='test'>Test ast</button>");

    window.button("Test ast",  std::map <std::string, std::string> { 
        { "class", "foo" }, 
        { "id", "button_id" },
    } );


    window.button("Test ast11111",  std::map <std::string, std::string> { 
        { "class", "foo" }, 
        { "id", "button_id1" },
    } );

    window.br();

    window.button("Test ffdasd",  std::map <std::string, std::string> { 
        { "class", "foo" }, 
        { "id", "button_id2" },
    } );



    window("#button_id").onclick([]() {
        std::cout << "test" << std::endl;
});

```
