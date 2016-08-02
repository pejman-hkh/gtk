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

                _xp, _yp, _max_yp = 20;
 
                //load css
    
                _provider = gtk_css_provider_new ();
                _display = gdk_display_get_default ();
                _screen = gdk_display_get_default_screen ( _display );
                
                
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
                _object = gtk_button_new_with_label ( str.c_str() );
            
                _create_widget( &attr );
    
            }

            void clicked( CallbackFunctionPtr callback ) {
                cout << "test" << endl;
            }
            
            void onclick( CallbackFunctionPtr callback ) {
                g_signal_connect (this->_ids[ this->_selector ], "clicked",  G_CALLBACK( callback ), NULL);
            }


            void text ( std::string str, std::map <std::string, std::string> attr ) {

                GtkTextBuffer *buffer;
                _object = gtk_text_view_new ();
                
                gtk_widget_set_size_request( _object, 50, 20 );
                 

                buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW ( _object ));
                gtk_text_view_set_editable(GTK_TEXT_VIEW ( _object ), FALSE);
                gtk_text_view_set_cursor_visible( GTK_TEXT_VIEW ( _object ), FALSE);
    
                gtk_text_buffer_set_text (buffer, str.c_str(), -1);


                std::string id = "#"+attr["id"];
                _buffers[ id ] = buffer;
                
                _create_widget( &attr );

                
            }
            
            void html( std::string str ) {
                gtk_text_buffer_set_text ( this->_buffers[ this->_selector ], str.c_str(), -1);
            }
            
            void label( std::string str, std::map <std::string, std::string> attr ) {
                
                _object = gtk_label_new ( str.c_str() );
                
                _create_widget( &attr );

            }

            void input ( std::string str, std::map <std::string, std::string> attr ) {


                _object = gtk_entry_new ();
                
                //gtk_style_context_add_class ( gtk_widget_get_style_context ( attr["class"].c_str() ), _object );
                
                
                gtk_entry_set_text ( GTK_ENTRY (_object), str.c_str() );
                
      
                _create_widget( &attr );
                
                
            }
            
            void link( std::map <std::string, std::string> attr ) {
                
              
                gtk_style_context_add_provider_for_screen (_screen, GTK_STYLE_PROVIDER (_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
                
                gsize bytes_written, bytes_read;

                GError *error = 0;

                gtk_css_provider_load_from_path (_provider, g_filename_to_utf8( attr["href"].c_str(), strlen( attr["href"].c_str() ), &bytes_read, &bytes_written, &error), NULL);

                
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
            
            /*void html( std::string str ) {

            }*/

            void br() {
                _yp += _max_yp + 5;
                _xp = 0;
            }

            ~Gtk() {
                g_object_unref (_provider);
                gtk_widget_show (_window);
                
                gtk_main();
            }

        
        private:
            
            void _create_widget( std::map <std::string, std::string> *attr ) {

                std::string id = "#"+(*attr)["id"];
                _ids[ id ] = _object;
                _types[ id ] = "label";
                
                //set id for usage in css
                gtk_widget_set_name ( GTK_WIDGET( _object ), (*attr)["id"].c_str() ); 
                
                //gtk_style_context_add_class ( gtk_widget_get_style_context ( (*attr)["class"].c_str() ), _object);


                gtk_fixed_put (GTK_FIXED (_fixed), _object, _xp, _yp );
                
                gtk_widget_show( _object );
     
                gint w1, w2;
                gtk_widget_get_preferred_width( _object, &w1, &w2 );
                
                gint h1, h2;
                gtk_widget_get_preferred_height( _object, &h1, &h2 );

                _xp += w2;

                std::cout << h2 << std::endl;
                
                _max_yp = h2;

            }
            
            gint _xp, _yp, _max_yp;
            GtkWidget * _window;
            GtkWidget * _object;
            GtkWidget * _fixed;
            std::map<std::string, GtkWidget*> _ids;
            std::map<std::string, GtkTextBuffer*> _buffers;
            std::map<std::string, std::string> _types;
            std::string _selector;
            
            GtkCssProvider *_provider;
            GdkDisplay *_display;
            GdkScreen *_screen;
                
    };
}


int main (int argc, char *argv[])
{
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
        
    return 0;
}
