#include "helpers.hpp"
#include "Cinder-Assimp/src/AssimpLoader.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#include "cinder/Camera.h"
#include "cinder/CameraUi.h"
#include "cinder/params/Params.h"

#include "Cinder-Assimp/src/SkeletalMesh.h"
#include "Cinder-Assimp/src/Renderer.h"

using namespace model;

class CinderApp : public App {
public:
	
	SkeletalMeshRef mActor;
	CameraPersp mCamera;
	CameraUi mCamUi;

	CinderApp() : App() {}
	~CinderApp() {}
	
	void setup() {
		model::Skeleton::sRenderMode = model::Skeleton::RenderMode::CLEANED;
		auto lambertShader = gl::getStockShader( gl::ShaderDef().color().lambert() );
		mActor = SkeletalMesh::create( AssimpLoader( loadResource( "lunez03.stl" ) ), nullptr, lambertShader );	
		mCamera.lookAt( vec3( 2.0f, 3.0f, 1.0f ), vec3( 0 ) );
		mCamera.setPerspective( 40.0f, getWindowAspectRatio(), 0.01f, 1000000.0f );
		mCamUi = CameraUi( &mCamera, getWindow() );
	}

	void draw() {
		gl::clear( Color::gray( 0.5f ) );
		gl::ScopedMatrices push;
		gl::setMatrices( mCamera );
		//gl::scale( mScaleFactor * vec3( 2.5f ) );

		gl::ScopedDepth depth( true );
	
		gl::ScopedColor color( Color::white() );
		model::Renderer::draw( mActor );
	}

	
	void fileDrop( FileDropEvent event ) {
		auto modelFile = loadFile( event.getFile( 0 ) );
		auto lambertShader = gl::getStockShader( gl::ShaderDef().color().lambert() );
		mActor = SkeletalMesh::create( AssimpLoader( modelFile), nullptr, lambertShader );
	}

	void keyDown( KeyEvent event ) {
		if( event.getCode() == KeyEvent::KEY_f ) {
			app::setFullScreen(! isFullScreen() );
		} else if( event.getCode() == KeyEvent::KEY_ESCAPE ) {
			quit();
		}
	}

	void resize() {
		mCamUi.setWindowSize( getWindowSize() );
		mCamera.setAspectRatio( getWindowAspectRatio() );
	}
};

CINDER_APP( CinderApp, RendererGl,  [&]( App::Settings *settings ) {
																			settings->setTitle("stl_viewer"); // watch the name != directory
																		})
