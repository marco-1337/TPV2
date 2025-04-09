// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
struct Transform;
struct Image;
struct ImageWithFrames;
struct Health;
struct Miraculous;
struct Immunity;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
	ImageWithFrames, \
	Health, \
	Miraculous, \
	Immunity

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	GHOSTS, \
	FRUITS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
class PacManSystem;
class GhostSystem;
class FoodSystem;
class ImmunitySystem;
class RenderSystem;
class CollisionsSystem;

#define _SYS_LIST_ \
	PacManSystem, \
	GhostSystem, \
	FoodSystem, \
	ImmunitySystem, \
	RenderSystem, \
	CollisionsSystem

