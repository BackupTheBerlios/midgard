%define dataname     data
%define develname    devel
%define group        Amusements/Games/RPG
%define _prefix      /usr
%ifarch x86_64
%define _libdir	     /usr/lib64
%endif


Name:         magus
Summary:      MAGUS - Create and manage Midgard characters
Summary(de):  MAGUS - Midgard Abenteurer Generieren Und Steigern
License:      GPL
Group:        %{group}
Version:      0.9.9.13
Release:      0.SuSE_9.2
Url:          http://midgard.berlios.de
Packager:     Alessandro Filippetti <sandro@filippetti.de>
Distribution: SuSE 9.2
Source0:      magus-0.9.9.13.tar.gz
BuildRoot:    %{_tmppath}/%{name}-%{version}-build
Prefix:       %{_prefix}
Requires:     %{name}-%{dataname} = %{version}
#Requires:      libsigc++20 >= 1.2
#Requires:      libsigc++2 >= 1.2
Requires:      gtkmm24 >= 2.0
# libsigc++2 und gtkmm2 sind bei SUSE 9.2 zu alt
BuildRequires: postgresql-devel
#BuildRequires: libsigc++20-devel >= 1.2
#BuildRequires: libsigc++2-devel
BuildRequires: gtkmm24-devel >= 2.0

%description
This is an RPM package for MAGUS.
MAGUS is a character generation and managing tool for the fantasy role playing
game Midgard. The binary package %{name}-%{version} contains only the
MAGUS executable and requires %{name}-%{dataname}-%{version} to run.
The executable is for %{distribution} and may fail to run under other systems.

Since libsigc++2 and gtkmm2 included in SuSE 9.2 are too old, libsic++2[0] 
and gtkmm24 are required. You'll find them here:

ftp://ftp.suse.com/pub/suse/%{arch}/supplementary/GNOME/update_for_9.2/development

To rebuild the packages from the source RPMs, you must build two times:
once with --target=i586 (or whatever your architecture is) and once with
--target=noarch.

%description -l de
Dies ist ein RPM-Paket f√ºr MAGUS.
MAGUS ist ein Abenteurer Generierungs- und Steigerungstool f√ºr das
Fantasyrollenspiel Midgard. Das Bin√§r-Paket %{name}-%{version} beinhaltet
nur das MAGUS-Executable und ben√∂tigt %{name}-%{dataname}-%{version}.
Das Executable wurde unter %{distribution} erstellt, so dass nicht
gew√§hrleistet ist, dass dieses Paket auch unter einer anderen
Konfiguration lauff√§hig ist.

Da die Pakete libsigc++2 und gtkmm2 von SuSE 9.2 zu alt sind, werden libsigc++2[0]
und gtkmm24 ben√∂tigt. Die Pakete finden sich unter:

ftp://ftp.suse.com/pub/suse/%{arch}/supplementary/GNOME/update_for_9.2/development

Zur Generierung der Pakete aus den Source RPMs ist der Build-Prozess
zweimal durchzuf√ºhren: einmal mit --target=i586 (oder einer anderen
Architektur) und einmal mit --target=noarch.

%package %{develname}
Summary:      MAGUS - Create and manage Midgard characters
Summary(de):  MAGUS - Midgard Abenteurer Generieren Und Steigern
Group:        %{group}
Copyright:    misc

%description %{develname}
MAGUS is a character generation and managing tool for the fantasy role playing
game Midgard. This package contains the header files and static libraries
which are needed only if you want to compile third-party programs which make
use of the MAGUS libraries. (It is not needed if you want to compile MAGUS
itself).

%description %{develname} -l de
MAGUS ist ein Abenteurer Generierungs- und Steigerungstool f√ºr das
Fantasyrollenspiel Midgard. Dieses RPM Paket beinhaltet die Header-Files
und statischen Bibliotheken, die Sie nur ben√∂tigen, wenn Sie Programme Dritter
compilieren wollen, die die MAGUS-Bibliotheken benutzen. (Zur Compilation von
MAGUS selbst ist dieses Paket nicht notwendig).

%ifarch noarch

%package %{dataname}
Summary:      MAGUS - Create and manage Midgard characters
Summary(de):  MAGUS - Midgard Abenteurer Generieren Und Steigern
Group:        %{group}
Copyright:    misc

%description %{dataname}
MAGUS is a character generation and managing tool for the fantasy role playing
game Midgard. This package contains datas and help screens necessary
to run MAGUS.

%description %{dataname} -l de
MAGUS ist ein Abenteurer Generierungs- und Steigerungstool f√ºr das
Fantasyrollenspiel Midgard. Dieses RPM Paket beinhaltet die f√ºr die
Benutzung von MAGUS notwendigen Daten und Hilfeseiten.

%endif

%prep
%setup -q

%build
%ifarch noarch
  exit 0
%endif
cd "$RPM_BUILD_DIR"/%{name}-%{version}
cd "$RPM_BUILD_DIR"/%{name}-%{version}/ManuProC_Base
aclocal -I macros
./autogen.sh --prefix=%{_prefix} --libdir=%{_libdir}

cd "$RPM_BUILD_DIR"/%{name}-%{version}/GtkmmAddons
aclocal
./autogen.sh

cd "$RPM_BUILD_DIR"/%{name}-%{version}/ManuProC_Widgets
aclocal -I macros
./autogen.sh 

cd "$RPM_BUILD_DIR"/%{name}-%{version}/midgard
aclocal
./autogen.sh --prefix=%{_prefix} --libdir=%{_libdir}

%install
cd "$RPM_BUILD_DIR"/%{name}-%{version}/midgard
%ifarch noarch
  mkdir -p %{buildroot}/%{_prefix}/share/magus/docs/
  cp src/*.tex src/*.png xml/*.xml %{buildroot}/%{_prefix}/share/magus/
  cp -R "$RPM_BUILD_DIR"/%{name}-%{version}/midgard/docs %{buildroot}/%{_prefix}/share/magus/
  rm $(find "%{buildroot}%{_prefix}/share/magus/docs/" | grep -e 'CVS\/[a-zA-Z]*')
  rmdir $(find "%{buildroot}%{_prefix}/share/magus/docs/" | grep CVS)
  exit 0
%else
  cd "$RPM_BUILD_DIR"/%{name}-%{version}/ManuProC_Base
  make DESTDIR='%{buildroot}' install
  cd "$RPM_BUILD_DIR"/%{name}-%{version}/midgard
  make DESTDIR='%{buildroot}' install
  strip --strip-unneeded %{buildroot}/%{_libdir}/*.so.*
  strip --strip-unneeded %{buildroot}/%{_prefix}/bin/*
  rm %{buildroot}/%{_prefix}/share/magus/*.png %{buildroot}/%{_prefix}/share/magus/*.xml %{buildroot}/%{_prefix}/share/magus/*.tex
%endif

#%clean

%ifnarch noarch

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(-,root,root)
%{_bindir}/*
%{_libdir}/*.so*
%{_prefix}/share/magus/LICENSE.pdf

%files %{develname}
%defattr(-,root,root)
%{_libdir}/*.a
%{_libdir}/*.la
%{_includedir}/*

%else

%files %{dataname}
%defattr(-,root,root)
%{_prefix}/share/magus/*

%endif

%changelog
* Fri Feb 17 2006 Alessandro Filippetti <sandro@filippetti.de>
- Vereinfachung nach der √úberarbeitung der Makefiles 
* Thu Jan 07 2006 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- Changed list of files so that several binaries will be packaged
* Thu Sep 23 2004 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- Brute-force patch of midgard/src/Makefile.am to work with automake-1.7.*
* Mon Sep 06 2004 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- Update to 0.9.7
- Use compiler option -fomit-frame-pointer
* Wed Nov 26 2003 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- minor compatibility improvements
* Sun Nov 02 2003 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- Corrected --define "fake 1" and related inconsistencies
* Tue Oct 21 2003 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- update to SuSE9.0 and magus-0.8.24
- added new options from midgard_cvs
- delete unneeded files before packaging (necessary for new rpmbuild)
- added --define "fake 1" option (works only with new rpmbuild)
* Fri Aug 01 2003 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- avoided unnecessary macros
- changed group
* Sat Jul 26 2003 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- copy data only for --target noarch (saves time)
- eliminated double calls of autogen.sh
* Sat Jul 19 2003 Martin V‰th <vaeth@mathematik.uni-wuerzburg.de>
- built from magus-rpm.spec and magus-rpm-data.spec

