/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:43:58 by phelebra          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:25 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_audio_file(t_track *dst, char *path)
{
	dst->loaded = cs_load_wav(path);
	if (dst->loaded.channels[0] == NULL)
		printf("- Failed to load audio %s:\n%s\n", path, cs_error_reason);
	dst->def = cs_make_def(&dst->loaded);
}

void	sound_play(t_box *box, t_track *sound)
{
	uint32_t	i;

	if (sound == NULL || sound->loaded.channels[0] == NULL)
		return ;
	i = 0;
	while (box->sound.playing[i].play != NULL && box->sound.playing[i].play->active == true && \
				i < sizeof(box->sound.playing) / sizeof(*box->sound.playing))
		i++;
	if (i == sizeof(box->sound.playing) / sizeof(*box->sound.playing))
		return ;
	box->sound.playing[i].play = cs_play_sound(box->sound.ctx, sound->def);
	if (box->sound.playing[i].play != NULL)
		cs_set_volume(box->sound.playing[i].play, box->sound.sfx_volume, box->sound.sfx_volume);
}
