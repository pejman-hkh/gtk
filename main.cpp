#include <gtk/gtk.h>
#include <iostream>
#include <map>
#include <string>
#include <regex>
#include <functional>

using namespace std;

extern "C" {
    
    
    struct _size {
        int width;
        int height;
    };
    
    typedef void(*CallbackFunctionPtr)();

    class Gtk {
        public:
            Gtk& init( int * argc, char **argv[] ) {
                gtk_init(argc, argv);   
                _window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                g_signal_connect( _window, "destroy", G_CALLBACK(gtk_main_quit), NULL );

                _fixed = gtk_fixed_new ();
                gtk_container_add (GTK_CONTAINER (_window), _fixed);
                gtk_widget_show (_fixed);

                _xp, _yp, _max_yp = 0;
 
                return *this;
            }

            Gtk() {

            }

            Gtk& operator()( std::string selector ){
                this->_selector = selector;
                return *this;
            }

            Gtk& set_size( int width, int height ) {
                gtk_window_set_default_size (GTK_WINDOW (_window), width, height);
                return *this;
            }

            Gtk& set_title( std::string title ) {
                gtk_window_set_title(GTK_WINDOW(_window), title.c_str() );
                return *this;
            }

            void button( std::string str, std::map <std::string, std::string> attr ) {

                std::string id = "#"+attr["id"];

                _object = gtk_button_new_with_label ( str.c_str() );

                _ids[ id ] = _object;
                _types[ id ] = "button";

                _create_widget();
    
            }

            void clicked( CallbackFunctionPtr callback ) {
                cout << "test" << endl;
            }
            
            void onclick( CallbackFunctionPtr callback ) {
                g_signal_connect (this->_ids[ this->_selector ], "clicked",  G_CALLBACK( callback ), NULL);
            }


            void label( std::string str, std::map <std::string, std::string> attr ) {
                std::string id = "#"+attr["id"];

                _object = gtk_label_new ( str.c_str() );

                _ids[ id ] = _object;
                _types[ id ] = "label";
                
                _create_widget();

            }

            void input ( std::string str, std::map <std::string, std::string> attr ) {

                std::string id = "#"+attr["id"];

                _object = gtk_entry_new ();

                gtk_entry_set_text ( GTK_ENTRY (_object), str.c_str() );
                
                _ids[ id ] = _object;
                _types[ id ] = "input";
                
                _create_widget();
                
                
            }
            
            Gtk &val( std::string str ) {
                
                if( _types[ _selector ] == "input" ) {
                    gtk_entry_set_text ( GTK_ENTRY ( this->_ids[ this->_selector ] ), str.c_str() );
                } else if( _types[ _selector ] == "label" ) {
                    gtk_label_set_text( GTK_LABEL( this->_ids[ this->_selector ] ), str.c_str() );
                }
                
                return *this;
            }
            
            std::string val() {
                const gchar *text = gtk_entry_get_text( GTK_ENTRY( this->_ids[ this->_selector ] ) );
                std::string ret = text;
                return ret;
            }
            
            void html( std::string str ) {

            }

            void br() {
                _yp += _max_yp;
                _xp = 0;
            }

            ~Gtk() {

                gtk_widget_show (_window);
                
                gtk_main();
            }

        
        private:
            
            void _create_widget() {
             
                gtk_fixed_put (GTK_FIXED (_fixed), _object, this->_xp, this->_yp );
                
                gtk_widget_show( _object );
     
                gint w1, w2;
                gtk_widget_get_preferred_width( _object, &w1, &w2 );
                
                gint h1, h2;
                gtk_widget_get_preferred_height( _object, &h1, &h2 );

                this->_xp += w2;

                _max_yp = h2;

            }
            
            gint _xp, _yp, _max_yp;
            GtkWidget * _window;
            GtkWidget * _object;
            GtkWidget * _fixed;
            std::map<std::string, GtkWidget*> _ids;
            std::map<std::string, std::string> _types;
            
            std::string _selector;
           
    };
}


int main (int argc, char *argv[])
{
    static Gtk window;
    window.init( &argc, &argv ).set_title( "test ast" ).set_size( 300, 100 );

    //window.body( "", )
    //window.load_html("index.html");
    
    //window.html("<button id='button_id' class='test'>Test ast</button>");
    
    typedef std::map <std::string, std::string> attr;
    
    window.label("Result : ",  attr { 
        { "class", "label" }, 
        { "id", "result" },
    } );
        
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
        
        window("#result").val( "username : "+ window("#username").val()+" password : "+window("#password").val() );
        
    });
    

    return 0;
}
