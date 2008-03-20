#!/bin/bash -e
# -*- Mode: Shell-script; tab-width: 4; indent-tabs-mode: nil; -*-
# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is mozilla.org code.
#
# The Initial Developer of the Original Code is
# Mozilla Corporation.
# Portions created by the Initial Developer are Copyright (C) 2006.
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#  Bob Clary <bob@bclary.com>
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

TEST_DIR=${TEST_DIR:-/work/mozilla/mozilla.com/test.mozilla.com/www}
TEST_BIN=${TEST_BIN:-$TEST_DIR/bin}
source ${TEST_BIN}/library.sh

source ${TEST_BIN}/set-build-env.sh $@

if [[ -z "$TREE" ]]; then
    error "source tree not specified!" $LINENO
fi

cd $TREE

case $product in
    firefox)
        if [[ ! ( -d mozilla && \
            -e mozilla/client.mk && \
            -e "mozilla/$project/config/mozconfig" ) ]]; then
            if ! eval cvs -z3 -q co $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS \
                mozilla/client.mk mozilla/$project/config/mozconfig; then
                error "during checkout of $project mozconfig" $LINENO
            fi
        fi

        cd mozilla

        if ! make -f client.mk checkout 2>&1; then
            error "during checkout of $project tree" $LINENO
        fi
        ;;

    thunderbird)
        if [[ ! ( -d mozilla && \
            -e mozilla/client.mk && \
            -e "mozilla/$project/config/mozconfig" ) ]]; then
            if ! eval cvs -z3 -q co $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS \
                mozilla/client.mk mozilla/$project/config/mozconfig; then
                error "during checkout of $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS $project mozconfig" $LINENO
            fi
        fi
        if [[ ! ( -d mozilla && \
            -e mozilla/client.mk && \
            -e "mozilla/browser/config/mozconfig" ) ]]; then
            if ! eval cvs -z3 -q co $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS \
                mozilla/client.mk mozilla/browser/config/mozconfig; then
                error "during checkout of $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS browser mozconfig" $LINENO
            fi
        fi

        cd mozilla

        if ! make -f client.mk checkout 2>&1; then
            error "during checkout of $project tree" $LINENO
        fi
        ;;

    js) 
        if [[ ! ( -d mozilla && \
            -e mozilla/js && \
            -e mozilla/js/src ) ]]; then
            if ! eval cvs -z3 -q co $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS mozilla/js; then
                error "during initial co $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS mozilla/js"
            fi
        fi

        cd mozilla/js/src

        if ! eval cvs -z3 -q update $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS -d -P 2>&1; then
            error "during update $MOZ_CO_FLAGS $BRANCH_CO_FLAGS $DATE_CO_FLAGS js/src" $LINENO
        fi

        if ! cvs -z3 -q update -d -P -A editline config  2>&1; then
            error "during checkout of js/src" $LINENO
        fi
        # end for js shell
        ;;
    *)
        error "unknown product $product" $LINENO
        ;;
esac
