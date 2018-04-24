// 
//  Font data for Arial 10pt
// 

#include "Arial_10pt.h"

// Character bitmaps for Arial 10pt
const uint8_t arial_10ptBitmaps[] = 
{
	// @0 '!' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  

	// @13 '"' (3 pixels wide)
	0xA0, // # #
	0xA0, // # #
	0xA0, // # #
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    

	// @26 '#' (8 pixels wide)
	0x12, //    #  # 
	0x12, //    #  # 
	0x22, //   #   # 
	0xFF, // ########
	0x24, //   #  #  
	0x24, //   #  #  
	0xFF, // ########
	0x48, //  #  #   
	0x48, //  #  #   
	0x48, //  #  #   
	0x00, //         
	0x00, //         
	0x00, //         

	// @39 '$' (5 pixels wide)
	0x70, //  ### 
	0xA8, // # # #
	0xA0, // # #  
	0xA0, // # #  
	0xE0, // ###  
	0x38, //   ###
	0x28, //   # #
	0xA8, // # # #
	0xA8, // # # #
	0x70, //  ### 
	0x20, //   #  
	0x00, //      
	0x00, //      

	// @52 '%' (10 pixels wide)
	0x61, 0x00, //  ##    #  
	0x92, 0x00, // #  #  #   
	0x92, 0x00, // #  #  #   
	0x94, 0x00, // #  # #    
	0x64, 0x00, //  ##  #    
	0x09, 0x80, //     #  ## 
	0x0A, 0x40, //     # #  #
	0x12, 0x40, //    #  #  #
	0x12, 0x40, //    #  #  #
	0x21, 0x80, //   #    ## 
	0x00, 0x00, //           
	0x00, 0x00, //           
	0x00, 0x00, //           

	// @78 '&' (8 pixels wide)
	0x30, //   ##    
	0x48, //  #  #   
	0x48, //  #  #   
	0x48, //  #  #   
	0x30, //   ##    
	0x60, //  ##     
	0x92, // #  #  # 
	0x8A, // #   # # 
	0x8C, // #   ##  
	0x73, //  ###  ##
	0x00, //         
	0x00, //         
	0x00, //         

	// @91 ''' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  

	// @104 '(' (3 pixels wide)
	0x20, //   #
	0x40, //  # 
	0x40, //  # 
	0x80, // #  
	0x80, // #  
	0x80, // #  
	0x80, // #  
	0x80, // #  
	0x80, // #  
	0x80, // #  
	0x40, //  # 
	0x40, //  # 
	0x20, //   #

	// @117 ')' (3 pixels wide)
	0x80, // #  
	0x40, //  # 
	0x40, //  # 
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x40, //  # 
	0x40, //  # 
	0x80, // #  

	// @130 '*' (5 pixels wide)
	0x20, //   #  
	0xF8, // #####
	0x20, //   #  
	0x50, //  # # 
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @143 '+' (7 pixels wide)
	0x00, //        
	0x00, //        
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0xFE, // #######
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        

	// @156 ',' (1 pixels wide)
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  

	// @169 '-' (3 pixels wide)
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0xE0, // ###
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    
	0x00, //    

	// @182 '.' (1 pixels wide)
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  

	// @195 '/' (4 pixels wide)
	0x10, //    #
	0x10, //    #
	0x20, //   # 
	0x20, //   # 
	0x20, //   # 
	0x40, //  #  
	0x40, //  #  
	0x40, //  #  
	0x80, // #   
	0x80, // #   
	0x00, //     
	0x00, //     
	0x00, //     

	// @208 '0' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  #### 
	0x00, //       
	0x00, //       
	0x00, //       

	// @221 '1' (3 pixels wide)
	0x20, //   #
	0x60, //  ##
	0xA0, // # #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x00, //    
	0x00, //    
	0x00, //    

	// @234 '2' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x04, //      #
	0x04, //      #
	0x04, //      #
	0x08, //     # 
	0x10, //    #  
	0x20, //   #   
	0x40, //  #    
	0xFC, // ######
	0x00, //       
	0x00, //       
	0x00, //       

	// @247 '3' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x04, //      #
	0x04, //      #
	0x38, //   ### 
	0x04, //      #
	0x04, //      #
	0x04, //      #
	0x84, // #    #
	0x78, //  #### 
	0x00, //       
	0x00, //       
	0x00, //       

	// @260 '4' (6 pixels wide)
	0x08, //     # 
	0x18, //    ## 
	0x18, //    ## 
	0x28, //   # # 
	0x28, //   # # 
	0x48, //  #  # 
	0x48, //  #  # 
	0xFC, // ######
	0x08, //     # 
	0x08, //     # 
	0x00, //       
	0x00, //       
	0x00, //       

	// @273 '5' (6 pixels wide)
	0x7C, //  #####
	0x40, //  #    
	0x40, //  #    
	0x80, // #     
	0xF8, // ##### 
	0x84, // #    #
	0x04, //      #
	0x04, //      #
	0x84, // #    #
	0x78, //  #### 
	0x00, //       
	0x00, //       
	0x00, //       

	// @286 '6' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x80, // #     
	0x80, // #     
	0xB8, // # ### 
	0xC4, // ##   #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  #### 
	0x00, //       
	0x00, //       
	0x00, //       

	// @299 '7' (6 pixels wide)
	0xFC, // ######
	0x08, //     # 
	0x08, //     # 
	0x10, //    #  
	0x10, //    #  
	0x20, //   #   
	0x20, //   #   
	0x40, //  #    
	0x40, //  #    
	0x40, //  #    
	0x00, //       
	0x00, //       
	0x00, //       

	// @312 '8' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  #### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  #### 
	0x00, //       
	0x00, //       
	0x00, //       

	// @325 '9' (6 pixels wide)
	0x78, //  #### 
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x8C, // #   ##
	0x74, //  ### #
	0x04, //      #
	0x04, //      #
	0x88, // #   # 
	0x70, //  ###  
	0x00, //       
	0x00, //       
	0x00, //       

	// @338 ':' (1 pixels wide)
	0x00, //  
	0x00, //  
	0x00, //  
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  

	// @351 ';' (1 pixels wide)
	0x00, //  
	0x00, //  
	0x00, //  
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x00, //  
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  

	// @364 '<' (6 pixels wide)
	0x00, //       
	0x00, //       
	0x04, //      #
	0x18, //    ## 
	0x60, //  ##   
	0x80, // #     
	0x60, //  ##   
	0x18, //    ## 
	0x04, //      #
	0x00, //       
	0x00, //       
	0x00, //       
	0x00, //       

	// @377 '=' (7 pixels wide)
	0x00, //        
	0x00, //        
	0x00, //        
	0xFE, // #######
	0x00, //        
	0x00, //        
	0xFE, // #######
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        

	// @390 '>' (6 pixels wide)
	0x00, //       
	0x00, //       
	0x80, // #     
	0x60, //  ##   
	0x18, //    ## 
	0x04, //      #
	0x18, //    ## 
	0x60, //  ##   
	0x80, // #     
	0x00, //       
	0x00, //       
	0x00, //       
	0x00, //       

	// @403 '?' (5 pixels wide)
	0x70, //  ### 
	0x88, // #   #
	0x88, // #   #
	0x08, //     #
	0x10, //    # 
	0x20, //   #  
	0x40, //  #   
	0x40, //  #   
	0x00, //      
	0x40, //  #   
	0x00, //      
	0x00, //      
	0x00, //      

	// @416 '@' (12 pixels wide)
	0x0F, 0x80, //     #####   
	0x30, 0x40, //   ##     #  
	0x40, 0x20, //  #        # 
	0x4E, 0x90, //  #  ### #  #
	0x91, 0x90, // #  #   ##  #
	0xA0, 0x90, // # #     #  #
	0xA1, 0x10, // # #    #   #
	0xA1, 0x20, // # #    #  # 
	0xA3, 0x20, // # #   ##  # 
	0x9D, 0xC0, // #  ### ###  
	0x40, 0x10, //  #         #
	0x20, 0x60, //   #      ## 
	0x1F, 0x80, //    ######   

	// @442 'A' (9 pixels wide)
	0x08, 0x00, //     #    
	0x14, 0x00, //    # #   
	0x14, 0x00, //    # #   
	0x14, 0x00, //    # #   
	0x22, 0x00, //   #   #  
	0x22, 0x00, //   #   #  
	0x7F, 0x00, //  ####### 
	0x41, 0x00, //  #     # 
	0x80, 0x80, // #       #
	0x80, 0x80, // #       #
	0x00, 0x00, //          
	0x00, 0x00, //          
	0x00, 0x00, //          

	// @468 'B' (7 pixels wide)
	0xFC, // ###### 
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0xFC, // ###### 
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0xFC, // ###### 
	0x00, //        
	0x00, //        
	0x00, //        

	// @481 'C' (7 pixels wide)
	0x38, //   ###  
	0x44, //  #   # 
	0x82, // #     #
	0x80, // #      
	0x80, // #      
	0x80, // #      
	0x80, // #      
	0x82, // #     #
	0x44, //  #   # 
	0x38, //   ###  
	0x00, //        
	0x00, //        
	0x00, //        

	// @494 'D' (7 pixels wide)
	0xF8, // #####  
	0x84, // #    # 
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x84, // #    # 
	0xF8, // #####  
	0x00, //        
	0x00, //        
	0x00, //        

	// @507 'E' (7 pixels wide)
	0xFE, // #######
	0x80, // #      
	0x80, // #      
	0x80, // #      
	0xFE, // #######
	0x80, // #      
	0x80, // #      
	0x80, // #      
	0x80, // #      
	0xFE, // #######
	0x00, //        
	0x00, //        
	0x00, //        

	// @520 'F' (6 pixels wide)
	0xFC, // ######
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0xF8, // ##### 
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x00, //       
	0x00, //       
	0x00, //       

	// @533 'G' (8 pixels wide)
	0x3C, //   ####  
	0x42, //  #    # 
	0x81, // #      #
	0x80, // #       
	0x80, // #       
	0x8F, // #   ####
	0x81, // #      #
	0x81, // #      #
	0x42, //  #    # 
	0x3C, //   ####  
	0x00, //         
	0x00, //         
	0x00, //         

	// @546 'H' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0xFE, // #######
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x00, //        
	0x00, //        
	0x00, //        

	// @559 'I' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  

	// @572 'J' (5 pixels wide)
	0x08, //     #
	0x08, //     #
	0x08, //     #
	0x08, //     #
	0x08, //     #
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      
	0x00, //      

	// @585 'K' (8 pixels wide)
	0x81, // #      #
	0x82, // #     # 
	0x84, // #    #  
	0x88, // #   #   
	0x90, // #  #    
	0xB0, // # ##    
	0xC8, // ##  #   
	0x84, // #    #  
	0x82, // #     # 
	0x81, // #      #
	0x00, //         
	0x00, //         
	0x00, //         

	// @598 'L' (6 pixels wide)
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0x80, // #     
	0xFC, // ######
	0x00, //       
	0x00, //       
	0x00, //       

	// @611 'M' (9 pixels wide)
	0x80, 0x80, // #       #
	0xC1, 0x80, // ##     ##
	0xC1, 0x80, // ##     ##
	0xA2, 0x80, // # #   # #
	0xA2, 0x80, // # #   # #
	0x94, 0x80, // #  # #  #
	0x94, 0x80, // #  # #  #
	0x94, 0x80, // #  # #  #
	0x88, 0x80, // #   #   #
	0x88, 0x80, // #   #   #
	0x00, 0x00, //          
	0x00, 0x00, //          
	0x00, 0x00, //          

	// @637 'N' (7 pixels wide)
	0x82, // #     #
	0xC2, // ##    #
	0xA2, // # #   #
	0xA2, // # #   #
	0x92, // #  #  #
	0x92, // #  #  #
	0x8A, // #   # #
	0x8A, // #   # #
	0x86, // #    ##
	0x82, // #     #
	0x00, //        
	0x00, //        
	0x00, //        

	// @650 'O' (8 pixels wide)
	0x3C, //   ####  
	0x42, //  #    # 
	0x81, // #      #
	0x81, // #      #
	0x81, // #      #
	0x81, // #      #
	0x81, // #      #
	0x81, // #      #
	0x42, //  #    # 
	0x3C, //   ####  
	0x00, //         
	0x00, //         
	0x00, //         

	// @663 'P' (7 pixels wide)
	0xFC, // ###### 
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0xFC, // ###### 
	0x80, // #      
	0x80, // #      
	0x80, // #      
	0x80, // #      
	0x00, //        
	0x00, //        
	0x00, //        

	// @676 'Q' (8 pixels wide)
	0x3C, //   ####  
	0x42, //  #    # 
	0x81, // #      #
	0x81, // #      #
	0x81, // #      #
	0x81, // #      #
	0x81, // #      #
	0x8D, // #   ## #
	0x42, //  #    # 
	0x3D, //   #### #
	0x00, //         
	0x00, //         
	0x00, //         

	// @689 'R' (7 pixels wide)
	0xFC, // ###### 
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0xFC, // ###### 
	0x88, // #   #  
	0x84, // #    # 
	0x84, // #    # 
	0x82, // #     #
	0x00, //        
	0x00, //        
	0x00, //        

	// @702 'S' (7 pixels wide)
	0x7C, //  ##### 
	0x82, // #     #
	0x82, // #     #
	0x80, // #      
	0x70, //  ###   
	0x0C, //     ## 
	0x02, //       #
	0x82, // #     #
	0x82, // #     #
	0x7C, //  ##### 
	0x00, //        
	0x00, //        
	0x00, //        

	// @715 'T' (7 pixels wide)
	0xFE, // #######
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x00, //        
	0x00, //        
	0x00, //        

	// @728 'U' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   # 
	0x38, //   ###  
	0x00, //        
	0x00, //        
	0x00, //        

	// @741 'V' (9 pixels wide)
	0x80, 0x80, // #       #
	0x80, 0x80, // #       #
	0x41, 0x00, //  #     # 
	0x41, 0x00, //  #     # 
	0x22, 0x00, //   #   #  
	0x22, 0x00, //   #   #  
	0x14, 0x00, //    # #   
	0x14, 0x00, //    # #   
	0x08, 0x00, //     #    
	0x08, 0x00, //     #    
	0x00, 0x00, //          
	0x00, 0x00, //          
	0x00, 0x00, //          

	// @767 'W' (13 pixels wide)
	0x82, 0x08, // #     #     #
	0x85, 0x08, // #    # #    #
	0x45, 0x10, //  #   # #   # 
	0x45, 0x10, //  #   # #   # 
	0x45, 0x10, //  #   # #   # 
	0x28, 0xA0, //   # #   # #  
	0x28, 0xA0, //   # #   # #  
	0x28, 0xA0, //   # #   # #  
	0x10, 0x40, //    #     #   
	0x10, 0x40, //    #     #   
	0x00, 0x00, //              
	0x00, 0x00, //              
	0x00, 0x00, //              

	// @793 'X' (7 pixels wide)
	0x82, // #     #
	0x44, //  #   # 
	0x44, //  #   # 
	0x28, //   # #  
	0x10, //    #   
	0x10, //    #   
	0x28, //   # #  
	0x44, //  #   # 
	0x44, //  #   # 
	0x82, // #     #
	0x00, //        
	0x00, //        
	0x00, //        

	// @806 'Y' (7 pixels wide)
	0x82, // #     #
	0x44, //  #   # 
	0x44, //  #   # 
	0x28, //   # #  
	0x28, //   # #  
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x10, //    #   
	0x00, //        
	0x00, //        
	0x00, //        

	// @819 'Z' (7 pixels wide)
	0x7E, //  ######
	0x04, //      # 
	0x08, //     #  
	0x08, //     #  
	0x10, //    #   
	0x10, //    #   
	0x20, //   #    
	0x20, //   #    
	0x40, //  #     
	0xFE, // #######
	0x00, //        
	0x00, //        
	0x00, //        

	// @832 '[' (2 pixels wide)
	0xC0, // ##
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0xC0, // ##

	// @845 '\' (4 pixels wide)
	0x80, // #   
	0x80, // #   
	0x40, //  #  
	0x40, //  #  
	0x40, //  #  
	0x20, //   # 
	0x20, //   # 
	0x20, //   # 
	0x10, //    #
	0x10, //    #
	0x00, //     
	0x00, //     
	0x00, //     

	// @858 ']' (2 pixels wide)
	0xC0, // ##
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0xC0, // ##

	// @871 '^' (5 pixels wide)
	0x00, //      
	0x20, //   #  
	0x50, //  # # 
	0x50, //  # # 
	0x50, //  # # 
	0x88, // #   #
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      
	0x00, //      

	// @884 '_' (7 pixels wide)
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0xFE, // #######

	// @897 '`' (2 pixels wide)
	0x80, // # 
	0x40, //  #
	0x00, //   
	0x00, //   
	0x00, //   
	0x00, //   
	0x00, //   
	0x00, //   
	0x00, //   
	0x00, //   
	0x00, //   
	0x00, //   
	0x00, //   

	// @910 'a' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x88, // #   #
	0x08, //     #
	0x78, //  ####
	0x88, // #   #
	0x98, // #  ##
	0x68, //  ## #
	0x00, //      
	0x00, //      
	0x00, //      

	// @923 'b' (5 pixels wide)
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0xB0, // # ## 
	0xC8, // ##  #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // #### 
	0x00, //      
	0x00, //      
	0x00, //      

	// @936 'c' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x88, // #   #
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      
	0x00, //      

	// @949 'd' (5 pixels wide)
	0x08, //     #
	0x08, //     #
	0x08, //     #
	0x68, //  ## #
	0x98, // #  ##
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x00, //      
	0x00, //      
	0x00, //      

	// @962 'e' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x88, // #   #
	0x88, // #   #
	0xF8, // #####
	0x80, // #    
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      
	0x00, //      

	// @975 'f' (4 pixels wide)
	0x30, //   ##
	0x40, //  #  
	0x40, //  #  
	0xE0, // ### 
	0x40, //  #  
	0x40, //  #  
	0x40, //  #  
	0x40, //  #  
	0x40, //  #  
	0x40, //  #  
	0x00, //     
	0x00, //     
	0x00, //     

	// @988 'g' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x68, //  ## #
	0x98, // #  ##
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x98, // #  ##
	0x68, //  ## #
	0x08, //     #
	0x88, // #   #
	0x70, //  ### 

	// @1001 'h' (5 pixels wide)
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0xB0, // # ## 
	0xC8, // ##  #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x00, //      
	0x00, //      
	0x00, //      

	// @1014 'i' (1 pixels wide)
	0x80, // #
	0x00, //  
	0x00, //  
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  

	// @1027 'j' (3 pixels wide)
	0x20, //   #
	0x00, //    
	0x00, //    
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0xC0, // ## 

	// @1040 'k' (5 pixels wide)
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x88, // #   #
	0x90, // #  # 
	0xA0, // # #  
	0xE0, // ###  
	0x90, // #  # 
	0x90, // #  # 
	0x88, // #   #
	0x00, //      
	0x00, //      
	0x00, //      

	// @1053 'l' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  
	0x00, //  

	// @1066 'm' (9 pixels wide)
	0x00, 0x00, //          
	0x00, 0x00, //          
	0x00, 0x00, //          
	0xB3, 0x00, // # ##  ## 
	0xCC, 0x80, // ##  ##  #
	0x88, 0x80, // #   #   #
	0x88, 0x80, // #   #   #
	0x88, 0x80, // #   #   #
	0x88, 0x80, // #   #   #
	0x88, 0x80, // #   #   #
	0x00, 0x00, //          
	0x00, 0x00, //          
	0x00, 0x00, //          

	// @1092 'n' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0xB0, // # ## 
	0xC8, // ##  #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x00, //      
	0x00, //      
	0x00, //      

	// @1105 'o' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      
	0x00, //      

	// @1118 'p' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0xB0, // # ## 
	0xC8, // ##  #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xC8, // ##  #
	0xB0, // # ## 
	0x80, // #    
	0x80, // #    
	0x80, // #    

	// @1131 'q' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x68, //  ## #
	0x98, // #  ##
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x98, // #  ##
	0x68, //  ## #
	0x08, //     #
	0x08, //     #
	0x08, //     #

	// @1144 'r' (3 pixels wide)
	0x00, //    
	0x00, //    
	0x00, //    
	0xA0, // # #
	0xC0, // ## 
	0x80, // #  
	0x80, // #  
	0x80, // #  
	0x80, // #  
	0x80, // #  
	0x00, //    
	0x00, //    
	0x00, //    

	// @1157 's' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x70, //  ### 
	0x88, // #   #
	0x80, // #    
	0x70, //  ### 
	0x08, //     #
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      
	0x00, //      

	// @1170 't' (3 pixels wide)
	0x00, //    
	0x40, //  # 
	0x40, //  # 
	0xE0, // ###
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x60, //  ##
	0x00, //    
	0x00, //    
	0x00, //    

	// @1183 'u' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x00, //      
	0x00, //      
	0x00, //      

	// @1196 'v' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x88, // #   #
	0x88, // #   #
	0x50, //  # # 
	0x50, //  # # 
	0x50, //  # # 
	0x20, //   #  
	0x20, //   #  
	0x00, //      
	0x00, //      
	0x00, //      

	// @1209 'w' (9 pixels wide)
	0x00, 0x00, //          
	0x00, 0x00, //          
	0x00, 0x00, //          
	0x88, 0x80, // #   #   #
	0x88, 0x80, // #   #   #
	0x55, 0x00, //  # # # # 
	0x55, 0x00, //  # # # # 
	0x55, 0x00, //  # # # # 
	0x22, 0x00, //   #   #  
	0x22, 0x00, //   #   #  
	0x00, 0x00, //          
	0x00, 0x00, //          
	0x00, 0x00, //          

	// @1235 'x' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x88, // #   #
	0x50, //  # # 
	0x50, //  # # 
	0x20, //   #  
	0x50, //  # # 
	0x50, //  # # 
	0x88, // #   #
	0x00, //      
	0x00, //      
	0x00, //      

	// @1248 'y' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0x88, // #   #
	0x88, // #   #
	0x50, //  # # 
	0x50, //  # # 
	0x50, //  # # 
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0xC0, // ##   

	// @1261 'z' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x00, //      
	0xF8, // #####
	0x10, //    # 
	0x10, //    # 
	0x20, //   #  
	0x40, //  #   
	0x40, //  #   
	0xF8, // #####
	0x00, //      
	0x00, //      
	0x00, //      

	// @1274 '{' (3 pixels wide)
	0x20, //   #
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x80, // #  
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x20, //   #

	// @1287 '|' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  

	// @1300 '}' (3 pixels wide)
	0x80, // #  
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x20, //   #
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x40, //  # 
	0x80, // #  

	// @1313 '~' (7 pixels wide)
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x72, //  ###  #
	0x9E, // #  ####
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
	0x00, //        
};

// Character descriptors for Arial 10pt
// { [Char width in bits], [Offset into arial_10ptCharBitmaps in bytes] }
const FONT_CHAR_INFO arial_10ptDescriptors[] = 
{
	{1, 0}, 		// ! 
	{3, 13}, 		// " 
	{8, 26}, 		// # 
	{5, 39}, 		// $ 
	{10, 52}, 		// % 
	{8, 78}, 		// & 
	{1, 91}, 		// ' 
	{3, 104}, 		// ( 
	{3, 117}, 		// ) 
	{5, 130}, 		// * 
	{7, 143}, 		// + 
	{1, 156}, 		// , 
	{3, 169}, 		// - 
	{1, 182}, 		// . 
	{4, 195}, 		// / 
	{6, 208}, 		// 0 
	{3, 221}, 		// 1 
	{6, 234}, 		// 2 
	{6, 247}, 		// 3 
	{6, 260}, 		// 4 
	{6, 273}, 		// 5 
	{6, 286}, 		// 6 
	{6, 299}, 		// 7 
	{6, 312}, 		// 8 
	{6, 325}, 		// 9 
	{1, 338}, 		// : 
	{1, 351}, 		// ; 
	{6, 364}, 		// < 
	{7, 377}, 		// = 
	{6, 390}, 		// > 
	{5, 403}, 		// ? 
	{12, 416}, 		// @ 
	{9, 442}, 		// A 
	{7, 468}, 		// B 
	{7, 481}, 		// C 
	{7, 494}, 		// D 
	{7, 507}, 		// E 
	{6, 520}, 		// F 
	{8, 533}, 		// G 
	{7, 546}, 		// H 
	{1, 559}, 		// I 
	{5, 572}, 		// J 
	{8, 585}, 		// K 
	{6, 598}, 		// L 
	{9, 611}, 		// M 
	{7, 637}, 		// N 
	{8, 650}, 		// O 
	{7, 663}, 		// P 
	{8, 676}, 		// Q 
	{7, 689}, 		// R 
	{7, 702}, 		// S 
	{7, 715}, 		// T 
	{7, 728}, 		// U 
	{9, 741}, 		// V 
	{13, 767}, 		// W 
	{7, 793}, 		// X 
	{7, 806}, 		// Y 
	{7, 819}, 		// Z 
	{2, 832}, 		// [ 
	{4, 845}, 		// \ 
	{2, 858}, 		// ] 
	{5, 871}, 		// ^ 
	{7, 884}, 		// _ 
	{2, 897}, 		// ` 
	{5, 910}, 		// a 
	{5, 923}, 		// b 
	{5, 936}, 		// c 
	{5, 949}, 		// d 
	{5, 962}, 		// e 
	{4, 975}, 		// f 
	{5, 988}, 		// g 
	{5, 1001}, 		// h 
	{1, 1014}, 		// i 
	{3, 1027}, 		// j 
	{5, 1040}, 		// k 
	{1, 1053}, 		// l 
	{9, 1066}, 		// m 
	{5, 1092}, 		// n 
	{5, 1105}, 		// o 
	{5, 1118}, 		// p 
	{5, 1131}, 		// q 
	{3, 1144}, 		// r 
	{5, 1157}, 		// s 
	{3, 1170}, 		// t 
	{5, 1183}, 		// u 
	{5, 1196}, 		// v 
	{9, 1209}, 		// w 
	{5, 1235}, 		// x 
	{5, 1248}, 		// y 
	{5, 1261}, 		// z 
	{3, 1274}, 		// { 
	{1, 1287}, 		// | 
	{3, 1300}, 		// } 
	{7, 1313}, 		// ~ 
};

// Font information for Arial 10pt
const FONT_INFO arial_10ptFontInfo =
{
	13, //  Character height
	'!', //  Start character
	'~', //  End character
	3, //  Width, in pixels, of space character
	arial_10ptDescriptors, //  Character descriptor array
	arial_10ptBitmaps, //  Character bitmap array
};