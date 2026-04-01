// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/MovieManager.h"
#include "Manager/GameManager.h"

void AMovieManager::Init()
{
	Super::Init();

	GetGameManager()->RecvCmsControllerPlay.AddUFunction(this, FName("CmsMoviePlay"));
	GetGameManager()->RecvCmsControllerPause.AddUFunction(this, FName("CmsMoviePause"));
	GetGameManager()->RecvCmsMovieClose.AddDynamic(this, &AMovieManager::CmsMovieClose);
}

void AMovieManager::SetMoviePlay()
{
	if (!IsFirstPlay)
		IsFirstPlay = true;

	MoviePlay();
}

void AMovieManager::SetMoviePause()
{
	MoviePause();
}

void AMovieManager::SetChangeMovieScene(MovieSceneType _type)
{
	ChangeMovieSource = VideoSources[(int)_type];
	NextSceneOpenSource();
}

void AMovieManager::CmsMoviePlay()
{
	if(IsFirstPlay)
		MoviePlay();
}

void AMovieManager::CmsMoviePause()
{
	if (IsFirstPlay)
		MoviePause();
}