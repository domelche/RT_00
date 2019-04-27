/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:14:15 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/04/27 16:14:54 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** boxes for all buttons
*/

const SDL_Rect g_btn_containers[] = (const SDL_Rect[]){

	(SDL_Rect){212, 51, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // save 
	// colors
	(SDL_Rect){212, 88, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // grayscale 
	(SDL_Rect){212, 109, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // inverted
	(SDL_Rect){103, 88, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // sepia
	(SDL_Rect){103, 109, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // ...
	// cam
	(SDL_Rect){212, 143, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // cam mode
	(SDL_Rect){103, 143, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // fov - 
	(SDL_Rect){39, 143, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // fov +
	// translation
	(SDL_Rect){212, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ox -
	(SDL_Rect){148, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ox +
	(SDL_Rect){212, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oy +
	(SDL_Rect){148, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oy +
	(SDL_Rect){212, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oz +
	(SDL_Rect){148, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oz +
	// rotation
	(SDL_Rect){102, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ox -
	(SDL_Rect){39, 179, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ox +
	(SDL_Rect){102, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oy +
	(SDL_Rect){39, 197, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oy +
	(SDL_Rect){102, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oz +
	(SDL_Rect){39, 216, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // oz +
	// skybox
	(SDL_Rect){212, 239, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT},
	// obj mode 
	(SDL_Rect){212, 278, DEFAULT_BUTTTON_WIDTH, DEFAULT_BUTTTON_HEIGHT}, // delete
	(SDL_Rect){75, 298, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // radius -
	(SDL_Rect){38, 298, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // radius +
	(SDL_Rect){75, 317, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // height -
	(SDL_Rect){38, 317, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // height +
	(SDL_Rect){75, 342, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // reflection -
	(SDL_Rect){38, 342, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // reflection +
	(SDL_Rect){75, 360, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // refl blur -
	(SDL_Rect){38, 360, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // refl blur +
	(SDL_Rect){75, 380, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // transp -
	(SDL_Rect){38, 380, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // transp +
	(SDL_Rect){75, 398, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // transp blur -
	(SDL_Rect){38, 398, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // transp blur +
	(SDL_Rect){75, 415, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // refract -
	(SDL_Rect){38, 415, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // refract +
	(SDL_Rect){75, 434, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // diffuse -
	(SDL_Rect){38, 434, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // diffuse +
	(SDL_Rect){75, 451, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ambient -
	(SDL_Rect){38, 451, ARROW_BUTTON_WIDTH, ARROW_BUTTON_HEIGHT}, // ambient +
	// Texturing
	(SDL_Rect){212, 493, TEXTURE_EDIT_BTN_W, TEXTURE_EDIT_BTN_H}, // color
	(SDL_Rect){160, 493, TEXTURE_EDIT_BTN_W, TEXTURE_EDIT_BTN_H}, // texture
	(SDL_Rect){109, 493, TEXTURE_EDIT_BTN_W, TEXTURE_EDIT_BTN_H}, // checker
	(SDL_Rect){57, 493, TEXTURE_EDIT_BTN_W, TEXTURE_EDIT_BTN_H}, // noise
	(SDL_Rect){211, 516, 28, 18}, // tex 1
	(SDL_Rect){176, 516, 28, 18}, // tex 2
	(SDL_Rect){141, 516, 28, 18}, // tex 3
	(SDL_Rect){107, 516, 28, 18}, // tex 4
	(SDL_Rect){72, 516, 28, 18}, // tex 5
	(SDL_Rect){37, 516, 28, 18} // tex 6
};

int			gui_init(t_sdl *sdl)
{
	SDL_Surface *image;
	SDL_Rect	r;

	if (IMG_Init(IMG_INIT_PNG) < 0)
		return -1;
	MLC_TEST((sdl->gui = (t_gui*)malloc(sizeof(t_gui))), "gui alloc failed!");
	MLC_TEST((image = IMG_Load(DEFAULT_GUI_TEX_NAME)),
	"gui texture could not loaded");
	MLC_TEST((sdl->gui->gui_texture =
	SDL_CreateTextureFromSurface(sdl->renderer, image)), "Texture could not created")
	SDL_FreeSurface(image);
	SDL_QueryTexture(sdl->gui->gui_texture, NULL, NULL, &(sdl->gui->w), &(sdl->gui->h));
	return 1;
}